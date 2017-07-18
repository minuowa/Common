#pragma once
template<typename T>
class CXWPtr : public std::weak_ptr<T> {
  public:
    typedef CXWPtr<T> MyType;
    typedef std::weak_ptr<T> Super;
    MyType& operator=(CXSPtr<T> rhs) {
        rhs.
    }
    T* operator->() {
        CXASSERT(this->expired());
        return this->lock();
    }
    operator bool() {
        return this->expired() && this->lock() != nullptr;
    }
};

