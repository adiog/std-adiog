// This file is a part of FreePoly project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <memory>

#define METHOD_CONTAINER(MethodContainer)                                      \
  struct MethodContainer {                                                     \
    template <typename ReturnType, typename T, typename... Args>               \
    static ReturnType method(const T &, Args...);                              \
  };

template <typename MethodContainerType, typename ReturnType, typename... Args>
class object_t {
private:
  template <typename T> struct model_t;

public:
  template <typename T, typename DecayT = std::remove_reference_t<T>>
  object_t(T &&val)
      : that(std::make_unique<model_t<DecayT>>(std::forward<T>(val))) {}

  object_t(const object_t &val) : that(val.that->copy()) {}
  object_t(object_t &&) noexcept = default;

  object_t &operator=(const object_t &val) {
    *this = object_t(val);
    return *this;
  }
  object_t &operator=(object_t &&) noexcept = default;

  ReturnType method_t(Args... args) const {
    return that->method(std::forward<Args>(args)...);
  }

private:
  struct concept_t {
    virtual ~concept_t() noexcept = default;
    virtual std::unique_ptr<concept_t> copy() const = 0;
    virtual ReturnType method(Args...) const = 0;
  };

  template <typename T> struct model_t final : concept_t {
    model_t(const T &val) : storage(val) {}

    model_t(T &&val) : storage(std::forward<T>(val)) {}

    ReturnType method(Args... args) const override {
      return MethodContainerType::template method<ReturnType, T, Args...>(
          storage, std::forward<Args>(args)...);
    }

    std::unique_ptr<concept_t> copy() const override {
      return std::make_unique<model_t<T>>(storage);
    }

  private:
    T storage;
  };

private:
  std::unique_ptr<concept_t> that;
};