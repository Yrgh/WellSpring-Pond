#pragma once
#include <string>

class NonCopyable {
public:
  NonCopyable() = default;
  ~NonCopyable() = default;

  NonCopyable(const NonCopyable &)            = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};

class NonMovable {
public:
  NonMovable() = default;
  ~NonMovable() = default;

  NonMovable(NonMovable &&) noexcept            = delete;
  NonMovable &operator=(NonMovable &&) noexcept = delete;
};

class Stationary : public NonCopyable, public NonMovable {
public:
  Stationary() = default;
  ~Stationary() = default;
};

/*
// RTTI marcos:
#define WSPOLY_BASE(name) \
public: \
inline virtual std::string getTypeName() const { return #name; } \
inline static std::string getStaticName() { return #name; } \
inline virtual bool _isType(const std::string &type_name) const { \
    return #name == type_name; \
} \
template<class T> \
inline bool isType() const { \
    return _isType(T::getStaticName()); \
} \
template <class T> \
inline T *downcast() { return isType<T>() ? (T *) this : nullptr; } \
private:

#define WSPOLY_CHILD(name, parent) \
public: \
inline std::string getTypeName() const override { return #name; } \
inline static std::string getStaticName() { return #name; } \
inline bool _isType(const std::string &type_name) const override { \
    if (#name == type_name) return true; \
    return parent::_isType(type_name); \
} \
private:

// Child of two parents
#define WSPOLY_BABY(name, parent1, parent2) \
public: \
inline std::string getTypeName() const override { return #name; } \
inline static std::string getStaticName() { return #name; } \
inline bool _isType(const std::string &type_name) const override { \
    if (#name == type_name) return true; \
    if (parent1::_isType(type_name)) return true; \
    return parent2::_isType(type_name); \
} \
private: */
