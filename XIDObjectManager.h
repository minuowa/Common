#pragma once
#include "XHashMap.h"
template<typename T>
class CXIDObjectManager
{
public:
    CXIDObjectManager ( void );
	~CXIDObjectManager();
    /** @brief
    	@return objID
    **/
    u32 addObj ( T* obj );
    void removeObj ( u32 id );
    void destoryObj ( u32 id );
    T* getObj ( u32 id );
protected:
    u32 mObjCount;
    CXHashMap<u32, T*> mObjMap;
};

template<typename T>
CXIDObjectManager<T>::~CXIDObjectManager()
{
	mObjCount=0;
	mObjMap.clear();
}

template<typename T>
CXIDObjectManager<T>::CXIDObjectManager ( void )
{
    mObjCount = 0;
}

template<typename T>
T* CXIDObjectManager<T>::getObj ( u32 id )
{
    T* obj = nullptr;
    mObjMap.Get ( id, obj );
    return obj;
}

template<typename T>
void CXIDObjectManager<T>::destoryObj ( u32 id )
{
    auto pair = mObjMap.find ( id );
    if ( pair != mObjMap.end() )
    {
        dSafeDelete ( pair->second );
        mObjMap.erase ( pair );
    }
}

template<typename T>
void CXIDObjectManager<T>::removeObj ( u32 id )
{
    mObjMap.erase ( id );
}

template<typename T>
u32 CXIDObjectManager<T>::addObj ( T* obj )
{
    mObjCount++;
    mObjMap.Insert ( mObjCount, obj );
    return mObjCount;
}

