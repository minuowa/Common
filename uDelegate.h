#pragma once
#include "uArray.h"
#include "base.h"
class uDelegate;
struct uEventArgs {
  public:
    virtual ~uEventArgs() {
    };
};
class uCallBack {
  public:
    virtual ~uCallBack() {
    }
    virtual void onCallBack(const uDelegate& d, uEventArgs*  e) {
    }
};

class uDelegate : public uArray<uCallBack*> {
  public:
    typedef uArray<uCallBack*> SuperType;
    virtual ~uDelegate(void) {
    }

    uDelegate& operator+= (uCallBack* callback) {
        CXASSERT(!this->Find(callback));
        this->push_back(callback);
        return *this;
    }
    uDelegate& operator-= (uCallBack* callback) {
        iterator iter = std::find(this->begin(), this->end(), callback);
        if (iter != this->end())
            this->erase(iter);
        return *this;
    }
    void trigger(uEventArgs* event = 0) {
        iterator iEnd = this->end();
        for (iterator i = this->begin(); i != iEnd; ++i) {
            uCallBack* callback = *i;
            callback->onCallBack(*this, event);
        }
    }
};
inline bool operator== (const uDelegate& lhs, const uDelegate& rhs) {
    return &lhs == &rhs;
}
