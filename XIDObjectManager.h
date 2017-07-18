#pragma once
#include "XHashMap.h"
template<typename T>
class UIDObjects {
  public:
    UIDObjects(void);
    ~UIDObjects();
    /** @brief
    @return objID
    **/
    u32 addObj(T* obj);
    void removeObj(u32 id);
    void destoryObj(u32 id);
    T* getObj(u32 id);
  protected:
    u32 mObjCount;
    CXHashMap<u32, T*> mObjMap;
};

template<typename T>
UIDObjects<T>::~UIDObjects() {
    mObjCount = 0;
    mObjMap.clear();
}

template<typename T>
UIDObjects<T>::UIDObjects(void) {
    mObjCount = 0;
}

template<typename T>
T* UIDObjects<T>::getObj(u32 id) {
    T* obj = nullptr;
    mObjMap.Get(id, obj);
    return obj;
}

template<typename T>
void UIDObjects<T>::destoryObj(u32 id) {
    auto pair = mObjMap.find(id);
    if (pair != mObjMap.end()) {
        dSafeDelete(pair->second);
        mObjMap.erase(pair);
    }
}

template<typename T>
void UIDObjects<T>::removeObj(u32 id) {
    mObjMap.erase(id);
}

template<typename T>
u32 UIDObjects<T>::addObj(T* obj) {
    mObjCount++;
    mObjMap.Insert(mObjCount, obj);
    return mObjCount;
}

