#pragma once
#include <memory>
template<typename T>
class CXSPtr : public std::shared_ptr<T> {
  public:
    typedef CXSPtr<T> MyType;
    typedef std::shared_ptr<T> Super;
    operator T* () {
        return this->get();
    }
    operator bool() {
        return this->get() != nullptr;
    }
    MyType& operator= (T* rhs) {
        this->reset(rhs);
        return *this;
    }
    CXSPtr(T* rhs)
        : Super(rhs) {
        this->reset(rhs);
    }
    CXSPtr() {
    }
};

