#ifndef XBuffer_h__
#define XBuffer_h__
//-------------------------------------------------------------------------
/**
	@brief
	@author nnboy,29/9/2014  12:08
*/
class CXBuffer
{
public:
    CXBuffer();
    ~CXBuffer();
    void reAllocate ( u32 byteSize );
    void reallocateByElementCount ( u32 cnt );
    void clear();
    inline void setElementByteCount ( u32 size );
    inline u32 length();
    inline u32 size();
    inline u32 capacity() const;
    inline char* getPointer();
    inline void copyTo ( void* dst );
    inline void copyFrom ( void* src );
    inline void setChar ( u32 idx, char c );
    template<typename T>
    void addElement ( T v );
    template<typename T>
    void addElement ( T* v, u32 cnt );

    //template<typename T>
    //T& operator[] ( u32 idx )
    //{
    //    return * ( ( T* ) &mData[idx * sizeof ( T )] );
    //}
    template<typename T>
    void set ( u32 idx, const T& v );
    template<typename T>
    inline T& get ( u32 idx )
    {
        return* ( ( T* ) &mData[idx * sizeof ( T )] ) ;
    }
protected:
    u32 mElementByteCount;
    u32 mCapacity;
    u32 mCount;
    char* mData;
};
inline u32 CXBuffer::length()
{
    return mCapacity * mElementByteCount;
}
inline char* CXBuffer::getPointer()
{
    return mData;
}
inline void CXBuffer::setElementByteCount ( u32 size )
{
    mElementByteCount = size;
}

inline void CXBuffer::copyTo ( void* dst )
{
    dMemoryCopy ( dst, mData, mCount * mElementByteCount );
}

inline void CXBuffer::copyFrom ( void* src )
{
    dMemoryCopy ( mData, src, mCapacity * mElementByteCount );
}
template<typename T>
inline void CXBuffer::addElement ( T* v, u32 cnt )
{
    dMemoryCopy ( &mData[mCount * mElementByteCount], v, cnt * mElementByteCount );
    mCount += cnt;
}

template<typename T>
inline void CXBuffer::addElement ( T v )
{
    * ( ( T* ) &mData[mCount * sizeof ( T )] ) = v;
    mCount++;
}
template<typename T>
void CXBuffer::set ( u32 idx, const T& v )
{
    * ( ( T* ) &mData[idx * sizeof ( T )] ) = v;
}

u32 CXBuffer::size()
{
    return mCount;
}

inline void CXBuffer::setChar ( u32 idx, char c )
{
    CXASSERT ( mData );
    mData[idx] = c;
}
inline u32 CXBuffer::capacity() const
{
    return mCapacity;
}

inline void CXBuffer::clear()
{
    mCount = 0;
}
#endif // XBuffer_h__
