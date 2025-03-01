#pragma once
#include <stdexcept>

namespace WellSpring::callable {
  enum class _FuncType {
    NONE = 0,
    FUNC,
    METHOD,
  };

  template<class Ret, class... Args> class _FunctionBase {
  public:
    virtual _FuncType getType() const { return _FuncType::NONE; }
    virtual Ret call(Args...) const = 0;
    virtual _FunctionBase *clone() const = 0;
    // other should be of the same type as this
    virtual bool equals(const _FunctionBase *other) const { return true; }
    int refcount = 0;
  };
  
  template<class Ret, class... Args> class _FunctionFunc : public _FunctionBase<Ret, Args...> {
  protected:
    typedef Ret (*FPtr)(Args...);
    FPtr _func; 
  public:
    _FuncType getType() const override { return _FuncType::FUNC; }
    Ret call(Args... args) const override { return _func(args...); }
    bool equals(const _FunctionBase<Ret, Args...> *other) const override {
      return _func == ((_FunctionFunc<Ret, Args...> *)(other))->_func;
    }
    
    _FunctionBase<Ret, Args...> *clone() const override {
      return new _FunctionFunc(*this);
    }
    
    _FunctionFunc(FPtr f) : _func(f) {}
    _FunctionFunc(const _FunctionFunc &other) : _func(other._func) {}
  };
  
  template<class T, class Ret, class... Args> class _FunctionMethod : public _FunctionBase<Ret, Args...> {
  protected:
    typedef Ret (T::*FPtr)(Args...);
    FPtr _func;
  public:
    // It hurt me brain, so I do dis
    T *_data;

    _FuncType getType() const override { return _FuncType::METHOD; }
    Ret call(Args... args) const override { 
      // Should we do it? Yes, but it isn't our job.
      //if (data == nullptr) throw std::exception();
      return (_data->*_func)(args...);
    }
    bool equals(const _FunctionBase<Ret, Args...> *other) const override {
      return _func == ((_FunctionMethod<T, Ret, Args...> *)(other))->_func && _data == ((_FunctionMethod<T, Ret, Args...> *)(other))->_data;
    }
    
    _FunctionBase<Ret, Args...> *clone() const override {
      return new _FunctionMethod(*this);
    }
    
    _FunctionMethod(FPtr method, T *obj) : _data(obj), _func(method) {}
    _FunctionMethod(const _FunctionMethod &other) : _data(other._data), _func(other._func) {}
  };
  
  template<class T> class Callable;
  
  template<class Ret, class... Args> class Callable<Ret(Args...)> {
    _FunctionBase<Ret, Args...> *_func;
    template<class F, class C> friend class _CallableLambdaContainer;

    template<class T>
    static Callable createExplicit(Ret (T::*method)(Args...), T *obj) {
      Callable result;
      result._func = new _FunctionMethod<T, Ret, Args...>(method, obj);
      result._func->refcount++;
      return result;
    }
  public:
    bool isValid() const {
      if (!_func) return false;
      if (_func->getType() == _FuncType::NONE) return false;
      return true;
    }
    
    Ret operator()(Args... args) const {
      // Better to warn them first
      if (!isValid()) throw std::runtime_error("Attempted to invoke an invalid Callable");
      return _func->call(args...);
    }

    Callable &operator=(const Callable &other) {
      if (other.isValid()) {
        if (_func) {
          _func->refcount--;
          if (_func->refcount <= 0)
            delete _func;
        }
        _func = other._func->clone();
        _func->refcount++;
      } else {
        throw std::invalid_argument("Attempted to set to an invalid Callable");
      }
      return *this;
    }

    bool operator==(const Callable &other) {
      if (other._func == _func) return true;
      if (other._func->getType() != other._func->getType()) return false;
      return _func->equals(other._func);
    }

    bool operator!=(const Callable &other) {
      return !(*this==other);
    }
    
    template<class T> Callable(Ret (T::*method)(Args...), T *obj) :
      _func(new _FunctionMethod<T, Ret, Args...>(method, obj))
    { _func->refcount++; }
    
    Callable(Ret (*f)(Args...)) : _func(new _FunctionFunc<Ret, Args...>(f)) { _func->refcount++; }
    Callable() : _func(nullptr) {}
    Callable(const Callable &other) {
      if (other.isValid()) {
        _func = other._func->clone();
        _func->refcount++;
      }
    }
    
    ~Callable() {
      if (_func) {
        _func->refcount--;
        // You never know...
        if (_func->refcount <= 0)
          delete _func;
      }
    }
  };

  template <class F, class C> class _CallableLambdaContainer;

  template<class F, class R, class... Args>
  class _CallableLambdaContainer<F, Callable<R(Args...)>> {
    struct SecretStruct {
        F fn;
        R call(Args... args) {
            return fn(args...);
        }
    };
  public:
    static Callable<R(Args...)> callableLambda(F func) {
      SecretStruct *anon = new SecretStruct{std::forward<F>(func)};
      return Callable<R(Args...)>::template createExplicit<SecretStruct>(&SecretStruct::call, anon);;
    }

    // A nice and ugly one-liner. Is it safe? GOD NO! Does it work? Probably...
    static void deleteLambda(Callable<R(Args...)> &callable) {
      delete ((_FunctionMethod<SecretStruct, R, Args...> *)(callable._func))->_data;
    }
  };

  // What kinda monster gets summoned when you say this?
  template<class R, class... Args> class _GeneratedCallableManagerBase {
  public:
    Callable<R(Args...)> result;
    virtual ~_GeneratedCallableManagerBase() {}
  };

  template<class F, class R, class... Args>
  class _GeneratedCallableManagerImpl : public _GeneratedCallableManagerBase<R, Args...> {
  public:
    ~_GeneratedCallableManagerImpl() {
      WellSpring::callable::_CallableLambdaContainer<F, Callable<R(Args...)>>::deleteLambda(
        _GeneratedCallableManagerBase<R, Args...>::result
      );
    }

    void create(F func) {
      _GeneratedCallableManagerBase<R, Args...>::result =
        WellSpring::callable::_CallableLambdaContainer<F, Callable<R(Args...)>>::callableLambda(func);
    }
  };

  template<class T> class FunctorBox;

  template<class R, class... Args> class FunctorBox<R(Args...)> {
    _GeneratedCallableManagerBase<R, Args...> *gcm;
  public:
    template<class F> FunctorBox(F func) {
      _GeneratedCallableManagerImpl<F, R, Args...> *new_gcm = new _GeneratedCallableManagerImpl<F, R, Args...>;
      new_gcm->create(func);
      gcm = new_gcm;
    }

    FunctorBox(const FunctorBox &other) {
      gcm = other.gcm;
      other.gcm = nullptr;
    }

    FunctorBox &operator=(const FunctorBox &other) {
      if (gcm) delete gcm;
      gcm = other.gcm;
      other.gcm = nullptr;
    }

    template<class F> FunctorBox &operator=(F func) {
      if (gcm)
        delete gcm;
      _GeneratedCallableManagerImpl<F, R, Args...> *new_gcm = new _GeneratedCallableManagerImpl<F, R, Args...>;
      new_gcm->create(func);
      gcm = new_gcm;
    }

    operator Callable<R(Args...)>() {
      if (!gcm) throw std::runtime_error("Invalid contents!");
      return gcm->result;
    }

    ~FunctorBox() {
      if (gcm)
        delete gcm;
    }
  };
}

// Export stuff
using WellSpring::callable::Callable;
using WellSpring::callable::FunctorBox;

// NOTE: Use this in a Callable constructor to make a Callable to an instance member function, especially an anonymous one
#define BIND_METHOD(instance, func) &decltype(instance)::func, &instance

template<class C, class F>
Callable<C> generateCallable(F func) {
  return WellSpring::callable::_CallableLambdaContainer<F, Callable<C>>::callableLambda(func);
}

template<class C, class F>
void deleteGeneratedCallable(Callable<C> callable) {
  return WellSpring::callable::_CallableLambdaContainer<F, Callable<C>>::deleteLambda(callable);
}