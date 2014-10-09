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
    void reAllocate ( XUI32 count );

	inline void setElementSize ( XUI32 size );
	inline XUI32 length();
    inline char* getPointer();
	inline void copyTo(void* dst);
	inline void copyFrom(void* src);
protected:
    XUI32 mElementSize;
    XUI32 mCount;
    char* mData;
};
inline XUI32 CXBuffer::length()
{
	return mCount * mElementSize;
}
inline char* CXBuffer::getPointer()
{
	return mData;
}
inline void CXBuffer::setElementSize( XUI32 size )
{
	mCount=size;
}

inline void CXBuffer::copyTo( void* dst )
{
	dMemoryCopy(dst,mData,this->length());
}

inline void CXBuffer::copyFrom(void* src)
{
	dMemoryCopy(mData,src,this->length());
}
#endif // XBuffer_h__
