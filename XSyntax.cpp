#include "base.h"
# include "XSyntax.h"
#include <regex>

using namespace std;

CXSyntax::CXSyntax ( void )
{
    mSystemElements.push_back ( new CXDefine );
    mSystemElements.push_back ( new CXCompile );
    mSystemElements.push_back ( new CXVariable );
    mSystemElements.push_back ( new CXFunctionDefine );
    mSystemElements.push_back ( new CXFunction );
    mSystemElements.push_back ( new CXClass );
    mSystemElements.push_back ( new CXHeader );
}


CXSyntax::~CXSyntax ( void )
{
}

//bool CXSyntax::parser ( const char* content )
//{
//    mCursor = 0;
//    assert ( content );
//    u32 len = dStrLen ( content );
//    mBuffer.reallocateByElementCount ( len + 1 );
//    mBuffer.copyFrom ( ( void* ) content );
//    return true;
//}

//bool CXSyntax::analyze()
//{
//    while ( !isEnd() )
//    {
//        char c = getNextChar();
//
//for ( auto e: mSystemElements )
//        {
//            if ( e->testEnd ( c ) )
//            {
//				//mContents.push_back(c.clone)
//            }
//        }
//for ( auto e: mSystemElements )
//        {
//            e->testEnd ( mCurString.c_str() );
//        }
//
//for ( auto e: mSystemElements )
//        {
//            e->testBegin ( c );
//        }
//for ( auto e: mSystemElements )
//        {
//            e->testBegin ( mCurString.c_str() );
//        }
//    }
//    return true;
//}

char CXSyntax::getNextChar()
{
    assert ( mCursor < mBuffer.capacity() );
    mCursor++;
    return mBuffer.get<char> ( mCursor );
}

bool CXSyntax::parser ( const char* content )
{
    mContent = content;
    regex pattern ( "#include.*?", regex_constants::extended );
    match_results<string::const_iterator> result;
    bool valid = regex_match ( mContent, result, pattern );
    return true;
}
