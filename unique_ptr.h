#ifndef H_UNIQUE_PTR
#define H_UNIQUE_PTR
#include <iostream>

template <class T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* other) : ptr_(other) {
  }

  UniquePtr(const UniquePtr<T>& other) = delete;

  UniquePtr& operator=(const UniquePtr<T>&) = delete;

  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T* Release() noexcept {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
    }
    ptr_ = ptr;
  }

  explicit operator bool() const {
    return Get() != nullptr;
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* operator->() const {
    return Get();
  }

  T& operator*() const {
    return *Get();
  }

  T* Get() const {
    return ptr_;
  }

  ~UniquePtr() {
    Reset();
  }
};
#endif