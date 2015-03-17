#pragma once
#include "luawrapper-master\luaFunction.h"
#include "luawrapper-master\luaClass.h"
#include "luawrapper-master\objpush.h"
#include "luawrapper-master\PopValue.h"
#include "luawrapper-master\luaWrapper.h"
using namespace luacpp;
//-------------------------------------------------------------------------
/**
	@brief lua script
	@notice:base class must regist before childclass,otherwise the method
			of base class may be not accessiable.
	@see:luacpp::reg_cclass
	@author nnboy,18/11/2014  17:10
*/
class CXLuaScript
{
public:
    CXLuaScript ( void );
    ~CXLuaScript ( void );

    bool init();

    lua_State* getState() const;

    bool doFile ( const char* name );
    bool doString ( const char* str );

    template<typename FUNC>
    void regGlobalFun ( const char* name, FUNC fun );

    template<typename CLASSNAME>
    luacpp::class_def<CLASSNAME> regClass ( const char* name );

    template<typename CLASSNAME, typename PARENT1>
    luacpp::class_def<CLASSNAME> regClass ( const char* name );

    template<typename CLASSNAME>
    void regClassCreator ( );


    template<typename CLASSNAME, typename FUNC>
    void regClassFunction ( const char* name, FUNC fun );

    template<typename CLASSNAME, typename FUNC>
    void regClassStaticFunction ( const char* name, FUNC fun );
    template<typename Ret>
    bool call ( Ret& ret, const char* funcname )
    {
        ret = luacpp::call<Ret> ( mState, funcname );
        return true;
    }
    template<typename Ret, typename Arg1>
    bool call ( Ret& ret, const char* funcname, Arg1 arg1 )
    {
        ret = luacpp::call<Ret> ( mState, funcname, arg1 );
        return true;
    }
    template<typename Ret, typename Arg1, typename Arg2>
    bool call ( Ret& ret, const char* funcname, Arg1 arg1, Arg2 arg2 )
    {
        ret = luacpp::call<Ret> ( mState, funcname, arg1, arg2 );
        return true;
    }
    template<typename Ret, typename Arg1, typename Arg2, typename Arg3>
    bool call ( Ret& ret, const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3 )
    {
        ret = luacpp::call<Ret> ( mState, funcname, arg1, arg2, arg3 );
        return true;
    }
    template<typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    bool call ( Ret& ret, const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4 )
    {
        ret = luacpp::call<Ret> ( mState, funcname, arg1, arg2, arg3, arg4 );
        return true;
    }
    template<typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    bool call ( Ret& ret, const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5 )
    {
        ret = luacpp::call<Ret> ( mState, funcname, arg1, arg2, arg3, arg4, arg5 );
        return true;
    }
    bool call ( const char* funcname )
    {
        luacpp::call<void> ( mState, funcname );
        return true;
    }
    template<typename Arg1>
    bool call ( const char* funcname, Arg1 arg1 )
    {
        luacpp::call<void> ( mState, funcname, arg1 );
        return true;
    }
    template<typename Arg1, typename Arg2>
    bool call ( const char* funcname, Arg1 arg1, Arg2 arg2 )
    {
        luacpp::call<void> ( mState, funcname, arg1, arg2 );
        return true;
    }
    template<typename Arg1, typename Arg2, typename Arg3>
    bool call ( const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3 )
    {
        luacpp::call<void> ( mState, funcname, arg1, arg2, arg3 );
        return true;
    }
    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    bool call ( const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4 )
    {
        luacpp::call<void> ( mState, funcname, arg1, arg2, arg3, arg4 );
        return true;
    }
    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    bool call ( const char* funcname, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5 )
    {
        luacpp::call<void> ( mState, funcname, arg1, arg2, arg3, arg4, arg5 );
        return true;
    }
private:
    luacpp::luaWrapper mLuaOwner;
    lua_State* mState;
};

template<typename CLASSNAME>
void CXLuaScript::regClassCreator()
{
    luacpp::class_def<CLASSNAME> regdClass ( mState );
    regdClass.constructor<void>();
}

CXDefineOnce CXLuaScript gLuaScript;

template<typename CLASSNAME, typename FUNC>
void CXLuaScript::regClassFunction ( const char* name, FUNC fun )
{
    luacpp::class_def<CLASSNAME> regdClass ( mState );
    regdClass.function ( name, fun );
}
template<typename CLASSNAME, typename FUNC>
void CXLuaScript::regClassStaticFunction ( const char* name, FUNC fun )
{
    luacpp::class_def<CLASSNAME> regdClass ( mState );
    regdClass.function ( name, fun );
}
template<typename CLASSNAME>
luacpp::class_def<CLASSNAME> CXLuaScript::regClass ( const char* name )
{
    return luacpp::reg_cclass<CLASSNAME>::_reg ( mState, name );
}
template<typename CLASSNAME, typename PARENT>
luacpp::class_def<CLASSNAME> CXLuaScript::regClass ( const char* name )
{
    return luacpp::reg_cclass<CLASSNAME, PARENT>::_reg ( mState, name );
}
template<typename FUNC>
void CXLuaScript::regGlobalFun ( const char* name, FUNC fun )
{
    luacpp::reg_cfun ( mState, name, fun );
}

inline CXLuaScript::CXLuaScript ( void )
	: mState ( nullptr )
{
}


inline CXLuaScript::~CXLuaScript ( void )
{
}

inline bool CXLuaScript::init()
{
	//mState = lua_open();
	mLuaOwner.init();
	mState = mLuaOwner;
	CXASSERT ( mState != nullptr );
	//luaopen_base ( mState );
	//luaL_openlibs ( mState );
	//luaopen_string ( mState );
	//luaopen_math ( mState );
	return true;
}

inline bool CXLuaScript::doFile ( const char* name )
{
	if ( 0 == luaL_dofile ( mState, name ) )
		return true;

	GString sError = lua_tostring ( mState, -1 );
	OutputDebugStringA ( "\n" );
	OutputDebugStringA ( sError );
	return false;
}

inline lua_State* CXLuaScript::getState() const
{
	return mState;
}

inline bool CXLuaScript::doString ( const char* str )
{
	if ( 0 == luaL_dostring ( mState, str ) )
		return true;

	GString sError = lua_tostring ( mState, -1 );
	OutputDebugStringA ( "\n" );
	OutputDebugStringA ( sError );
	return true;
}