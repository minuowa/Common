#ifndef uBuffer_h__
#define uBuffer_h__
//-------------------------------------------------------------------------
/**
	@brief
	@author nnboy,29/9/2014  12:08
*/
class uBuffer
{
public:
    uBuffer();
    ~uBuffer();
    uBuffer ( u32 byteCnt );
    void reAllocate ( u32 byteSize );
    void reallocateByElementCount ( u32 cnt );
    void clear();
    inline void setElementByteCount ( u32 size );
    inline u32 length();
    inline u32 size();
    inline void setSize ( u32 size );
    inline u32 capacity() const;
    inline char* getPointer();
    inline wchar_t* getWChar();
    inline const char* getString() const;
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

    inline void zero()
    {
        dMemoryZero ( mData, length() );
    }


protected:
    u32 mElementByteCount;
    u32 mCapacity;
    u32 mCount;
    union
    {
        char* mData;
        wchar_t* mWData;
    };
};
inline u32 uBuffer::length()
{
    return mCapacity * mElementByteCount;
}
inline char* uBuffer::getPointer()
{
    return mData;
}
inline const char* uBuffer::getString() const
{
    return ( const char* ) mData;
}
inline void uBuffer::setElementByteCount ( u32 size )
{
    mElementByteCount = size;
}

inline void uBuffer::copyTo ( void* dst )
{
    dMemoryCopy ( dst, mData, mCount * mElementByteCount );
}

inline void uBuffer::copyFrom ( void* src )
{
    dMemoryCopy ( mData, src, mCapacity * mElementByteCount );
}
template<typename T>
inline void uBuffer::addElement ( T* v, u32 cnt )
{
    dMemoryCopy ( &mData[mCount * mElementByteCount], v, cnt * mElementByteCount );
    mCount += cnt;
}

template<typename T>
inline void uBuffer::addElement ( T v )
{
    * ( ( T* ) &mData[mCount * sizeof ( T )] ) = v;
    mCount++;
}
template<typename T>
inline void uBuffer::set ( u32 idx, const T& v )
{
    * ( ( T* ) &mData[idx * sizeof ( T )] ) = v;
}

inline u32 uBuffer::size()
{
    return mCount;
}

inline void uBuffer::setChar ( u32 idx, char c )
{
    CXASSERT ( mData );
    mData[idx] = c;
}
inline u32 uBuffer::capacity() const
{
    return mCapacity;
}

inline void uBuffer::clear()
{
    mCount = 0;
    dMemoryZero ( mData, length() );
}
inline uBuffer::uBuffer ( void )
{
    mData = 0;
    mCount = 0;
    mCapacity = 0;
    mElementByteCount = 1;
}
inline uBuffer::uBuffer ( u32 byteCnt )
{
    mData = 0;
    mCount = 0;
    mCapacity = byteCnt;
    mElementByteCount = 1;
    reAllocate ( mCapacity );
}


inline uBuffer::~uBuffer ( void )
{
    dSafeDelete ( mData );
}

inline void uBuffer::reAllocate ( u32 byteSize )
{
    dSafeDelete ( mData );
    mData = new char[byteSize];
    if ( mElementByteCount > 0 )
        mCapacity = byteSize / mElementByteCount;
    dMemoryZero ( mData, byteSize );
}

inline void uBuffer::reallocateByElementCount ( u32 cnt )
{
    dSafeDelete ( mData );
    mCapacity = cnt;
    mData = new char[mCapacity * mElementByteCount];
    dMemoryZero ( mData, mCapacity * mElementByteCount );
}

inline void uBuffer::setSize ( u32 size )
{
    mCount = size;
}

inline wchar_t* uBuffer::getWChar()
{
    return mWData;
}

#endif // uBuffer_h__
