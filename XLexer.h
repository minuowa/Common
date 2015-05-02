#pragma once
#include "uString.h"
#include "XHashMap.h"
template<typename CH>
class CXToken
{
public:
    int mType;
    const CH* mStr;
public:
    CXToken();
};
enum eCharState
{
    eCharStateNone,
    eCharStateVar,
};
template<typename CH>
class CXLexer
{
public:
    typedef CXToken<CH> MyToken;
    static const int ErrorTokenType = -1;
public:
    CXLexer ( void );
    ~CXLexer ( void );
    bool parser ( const CH* content );
    void bind ( int type, const CH* str );
    void next ( MyToken& token );
    inline bool isEnd();
    inline bool isTokenTypeValid() const;
protected:
    int getTokenType ( const CH* str ) const;
    inline CH getNextChar();

    CXHashMap<std::basic_string<CH>, int> mTokenMap;
    uBuffer mBuffer;
    std::basic_string<CH> mCurString;
    u32 mLine;
    u32 mCursor;
    eCharState mState;
};

template<typename CH>
CXLexer<CH>::~CXLexer ( void )
{
}

template<typename CH>
int CXLexer<CH>::getTokenType ( const CH* str ) const
{
    int type = -1;
    mTokenMap.Get ( str, type );
    return type;
}

template<typename CH>
inline bool CXLexer<CH>::isEnd()
{
    return mCursor >= mBuffer.capacity();
}

template<typename CH>
void CXLexer<CH>::next ( MyToken& token )
{
    mCurString.clear();
    while ( !isEnd() )
    {
        CH c = getNextChar();

        switch ( c )
        {
        case '\n':
        {
            mLine++;
        }
        case ' ':
        case '\t':
        case ',':
        case ':':
        case '&':
        case ';':
        case '#':
        case '{':
        case '}':
        case '(':
        case ')':
        {
            if ( mState == eCharStateVar )
            {
                token.mStr = mCurString.c_str();
                token.mType = getTokenType ( token.mStr );
                mState = eCharStateNone;
                //OutputDebugStringA ( "\n" );
                //OutputDebugStringA ( token.mStr );
                return;
            }
        }
        break;
        default:
        {
            mCurString.append ( 1, c );
            mState = eCharStateVar;
        }
        break;
        }
    }
}

template<typename CH>
CH CXLexer<CH>::getNextChar()
{
    assert ( mCursor < mBuffer.capacity() );
    mCursor++;
    return mBuffer.get<CH> ( mCursor );
}
template<typename CH>
CXLexer<CH>::CXLexer ( void )
{
    mCursor = 0;
    mLine = 1;
    mState = eCharStateVar;
    mBuffer.setElementByteCount ( sizeof ( CH ) );
}

template<typename CH>
void CXLexer<CH>::bind ( int type, const CH* str )
{
    assert ( !mTokenMap.findkey ( str ) );
    mTokenMap.Insert ( str, type );
}

template<typename CH>
bool CXLexer<CH>::parser ( const CH* content )
{
    mCursor = 0;
    assert ( content );
    u32 len = dStrLen ( content );
    mBuffer.reallocateByElementCount ( len + 1 );
    mBuffer.copyFrom ( ( void* ) content );
    return true;
}

template<typename CH>
CXToken<CH>::CXToken()
    : mType ( CXLexer<CH>::ErrorTokenType )
    , mStr ( nullptr )
{
}
typedef CXToken<char> CXCharToken;
typedef CXToken<wchar_t> CXWCharToken;

typedef CXLexer<char> CXCharLexer;
typedef CXLexer<wchar_t> CXWCharLexer;