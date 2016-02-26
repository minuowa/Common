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
    uBuffer ( size_t byteCnt );
    void reAllocate ( size_t byteSize );
    void reallocateByElementCount ( size_t cnt );
    void clear();
    inline void setElementByteCount ( size_t size );
    inline size_t length();
    inline size_t size();
    inline void setSize ( size_t size );
    inline size_t capacity() const;
    inline char* getPointer() const;
    inline wchar_t* getWChar();
    inline const char* getString() const;
    inline void copyTo ( void* dst );
    inline void copyFrom ( void* src );
    inline void setChar ( size_t idx, char c );
    template<typename T>
    void addElement ( T v );
    template<typename T>
    void addElement ( T* v, size_t cnt );
	void addString(const char* str);
    //template<typename T>
    //T& operator[] ( u32 idx )
    //{
    //    return * ( ( T* ) &mData[idx * sizeof ( T )] );
    //}
    template<typename T>
    void set ( size_t idx, const T& v );
    template<typename T>
    inline T& get ( size_t idx )
    {
        return* ( ( T* ) &mData[idx * sizeof ( T )] ) ;
    }

    inline void zero()
    {
        dMemoryZero ( mData, length() );
    }


protected:
    size_t mElementByteCount;
    size_t mCapacity;
    size_t mCount;
    union
    {
        char* mData;
        wchar_t* mWData;
    };
};
inline size_t uBuffer::length()
{
    return mCapacity * mElementByteCount;
}
inline char* uBuffer::getPointer() const
{
    return mData;
}
inline const char* uBuffer::getString() const
{
    return ( const char* ) mData;
}
inline void uBuffer::setElementByteCount ( size_t size )
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
inline void uBuffer::addElement ( T* v, size_t cnt )
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
inline void uBuffer::set ( size_t idx, const T& v )
{
    * ( ( T* ) &mData[idx * sizeof ( T )] ) = v;
}

inline size_t uBuffer::size()
{
    return mCount;
}

inline void uBuffer::setChar ( size_t idx, char c )
{
    CXASSERT ( mData );
    mData[idx] = c;
}
inline size_t uBuffer::capacity() const
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
inline uBuffer::uBuffer ( size_t byteCnt )
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

inline void uBuffer::reAllocate ( size_t byteSize )
{
    dSafeDelete ( mData );
    mData = new char[byteSize];
    if ( mElementByteCount > 0 )
        mCapacity = byteSize / mElementByteCount;
    dMemoryZero ( mData, byteSize );
}

inline void uBuffer::reallocateByElementCount ( size_t cnt )
{
    dSafeDelete ( mData );
    mCapacity = cnt;
    mData = new char[mCapacity * mElementByteCount];
    dMemoryZero ( mData, mCapacity * mElementByteCount );
}

inline void uBuffer::setSize ( size_t size )
{
    mCount = size;
}

inline wchar_t* uBuffer::getWChar()
{
    return mWData;
}

inline void uBuffer::addString( const char* str )
{
	CXASSERT(str);
	CXASSERT ( mData );
	CXASSERT(mElementByteCount==1);
	size_t cnt=strlen(str)+1;
	dMemoryCopy ( &mData[mCount * mElementByteCount], (void*)str, cnt * mElementByteCount );
	mCount += cnt;
}

#endif // uBuffer_h__
