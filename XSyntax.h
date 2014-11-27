#pragma once
#include "XStack.h"
#include "XDynaArray.h"
#include "XString.h"
#include "XHashMap.h"
#include "XBuffer.h"
class CXElement
{
public:
    virtual bool testBegin ( char c );
    virtual bool testBegin ( const char* str );
    virtual bool testEnd ( char c );
    virtual bool testEnd ( const char* str );
	virtual void clear();
	virtual CXElement* clone();
protected:
	bool mBegin;
};
class CXDefine: public CXElement
{

};
class  CXCompile: public CXElement
{

};
class CXVariable: public CXElement
{

};
class CXFunctionDefine: public CXElement
{

};
class CXFunction: public CXElement
{

};
class CXClass: public CXElement
{
};
class CXHeader: public CXElement
{

};
class CXSyntax
{
public:
    CXSyntax ( void );
    ~CXSyntax ( void );

public:
	bool parser ( const char* content );
	void bind ( int type, const char* str );
	inline bool isEnd();
protected:
	bool analyze();
	int getTokenType ( const char* str ) const;
	inline char getNextChar();
protected:
	std::string mContent;
	CXDynaArray<CXElement*> mSystemElements;
	CXHashMap<CXCharString<char>, int> mTokenMap;
	CXBuffer mBuffer;
	CXCharString<char> mCurString;
	u32 mLine;
	u32 mCursor;
	//eCharState mState;
    CXDynaArray<CXElement*> mContents;
    CXStack<CXElement*> mStack;
};

