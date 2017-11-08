// This file is a part of FreePoly project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <memory>

template <typename T, typename ReturnType, typename... Args>
ReturnType free_method_t(const T &, Args...);

template <typename ReturnType, typename... Args> class object_t {
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
    return that->method_t(std::forward<Args>(args)...);
  }

private:
  struct concept_t {
    virtual ~concept_t() noexcept = default;
    virtual std::unique_ptr<concept_t> copy() const = 0;
    virtual ReturnType method_t(Args...) const = 0;
  };

  template <typename T> struct model_t final : concept_t {
    model_t(const T &val) : storage(val) {}
    model_t(T &&val) : storage(std::forward<T>(val)) {}
    ReturnType method_t(Args... args) const override {
      return free_method_t<T, ReturnType, Args...>(storage,
                                                   std::forward<Args>(args)...);
    }
    std::unique_ptr<concept_t> copy() const override {
      return std::make_unique<model_t<T>>(storage);
    }
    T storage;
  };

  std::unique_ptr<concept_t> that;
};