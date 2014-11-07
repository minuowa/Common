#include "base.h"
#include "XLuaScript.h"
#include "XString.h"
CXLuaScript gLuaScript;

CXLuaScript::CXLuaScript ( void )
    : mState ( nullptr )
{
}


CXLuaScript::~CXLuaScript ( void )
{
}

bool CXLuaScript::init()
{
    //mState = lua_open();
	mLuaOwner.init();
	mState=mLuaOwner;
    CXASSERT ( mState != nullptr );
    //luaopen_base ( mState );
    //luaL_openlibs ( mState );
    //luaopen_string ( mState );
    //luaopen_math ( mState );
    return true;
}

bool CXLuaScript::doFile ( const char* name )
{
    if ( 0 == luaL_dofile ( mState, name ) )
        return true;

    GString sError = lua_tostring ( mState, -1 );
	OutputDebugStringA ( "\n" );
	OutputDebugStringA ( sError );
    return false;
}

lua_State* CXLuaScript::getState() const
{
	return mState;
}
