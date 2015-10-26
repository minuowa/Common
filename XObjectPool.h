#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
#include <memory>

using std::queue;
using std::vector;
/** @brief ObjectPool
		T* p=new T();
			1:T::operator new(size_t) (If doesn't have this function,call system's.Acquire one memory and get the address P)
			2:p->T()
			3:return P
		delete p;
			1:p->~T();
			2:p->operator delete(p);
	@author nnboy,7/11/2014  23:56
	**/
template <typename T>
class CXObjectPool
{
public:
    CXObjectPool ( int chunkSize = mDefaultChunkSize );
    ~CXObjectPool();

    inline T* acquireObject();
    inline void releaseObject ( void* obj );

    int getFreeNum()
    {
        return mFreeList.size();
    }
    void allocateChunk ( int chunkSize = mDefaultChunkSize );
protected:
    class queue<T*> mFreeList;
    class vector<T*> mAllObjects;

    int mChunkSize;
    static const int mDefaultChunkSize = 32;
private:
    CXObjectPool ( const CXObjectPool<T>& rhs );
    CXObjectPool & operator= ( const CXObjectPool<T>& rhs );
};

template <typename T>
CXObjectPool<T>::CXObjectPool ( int chunkSize ) /*throw ( std::invalid_argument, std::bad_alloc )*/
    : mChunkSize ( chunkSize )
{
    if ( mChunkSize <= 0 )
    {
        throw std::invalid_argument ( "chunk size must be positive" );
    }
    allocateChunk ( mChunkSize );
}

template <typename T>
void CXObjectPool<T>::allocateChunk ( int chunkSize )
{
    for ( int i = 0; i < chunkSize; ++i )
	{
		T * block = new T() ;
		mAllObjects.push_back ( block );
		mFreeList.push ( block );
	}
}


template <typename T>
CXObjectPool<T>::~CXObjectPool()
{
for ( auto p: mAllObjects )
        delete ( p );
}

template <typename T>
inline T* CXObjectPool<T>::acquireObject()
{
    if ( mFreeList.empty() )
        allocateChunk ( mChunkSize );
    T *pobj = mFreeList.front();
    mFreeList.pop();
    return pobj;
}

template <typename T>
inline void CXObjectPool<T>::releaseObject ( void* obj )
{
    if ( obj != nullptr )
    {
        mFreeList.push ( ( T* ) obj );
    }
}
#define CXDeclareObjectPool(type) \
	public:\
	static CXObjectPool<type> mPool##type;\
		static void* operator new ( unsigned int n )\
		{\
		return mPool##type.acquireObject();\
		}\
		static void operator delete ( void* p )\
		{\
		mPool##type.releaseObject ( p );\
		}

#define CXImpleteObjectPool(type) \
	CXObjectPool<type> type::mPool##type();

#define CXImpleteObjectPoolN(type,n) \
	CXObjectPool<type> type::mPool##type ( n );
