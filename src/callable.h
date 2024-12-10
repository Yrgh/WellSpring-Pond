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
    T *_data;
    
    typedef Ret (T::*FPtr)(Args...);
    FPtr _func; 
  public:
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
  protected:
    _FunctionBase<Ret, Args...> *_func;
  private:
    template <class F, class C> friend class _CallableLambdaContainer;

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

  template <class F, class C>
  class _CallableLambdaContainer {
  public:
    static C callableLambda(F func);
  };

  template<class F, class R, class... Args>
  class _CallableLambdaContainer<F, Callable<R(Args...)>> {
  public:
    static Callable<R(Args...)> callableLambda(F func) {
      struct SecretStruct {
          F fn;
          R call(Args... args) {
              return fn(args...);
          }
      };
      SecretStruct *anon = new SecretStruct{std::forward<F>(func)};
      Callable<R(Args...)> result = Callable<R(Args...)>::template createExplicit<SecretStruct>(&SecretStruct::call, anon);
      return result;
    }
  };
}

// Export Callable
using WellSpring::callable::Callable;

// NOTE: Use this in a Callable constructor to make a Callable to an instance member function, especially an anonymous one
#define BIND_METHOD(instance, func) &decltype(instance)::func, &instance

template<class C, class F>
Callable<C> generateCallable(F func) {
  return WellSpring::callable::_CallableLambdaContainer<F, Callable<C>>::callableLambda(func);
}