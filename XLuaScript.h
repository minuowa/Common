#pragma once
#include "luawrapper-master\luaFunction.h"
#include "luawrapper-master\luaClass.h"
#include "luawrapper-master\objpush.h"
#include "luawrapper-master\PopValue.h"
#include "luawrapper-master\luaWrapper.h"
using namespace luacpp;

class CXLuaScript
{
public:
    CXLuaScript ( void );
    ~CXLuaScript ( void );

    bool init();

	lua_State* getState() const;

    bool doFile ( const char* name );

    template<typename FUNC>
    void regGlobalFun ( const char* name, FUNC fun );

    template<typename CLASSNAME>
    luacpp::class_def<CLASSNAME> regClass ( const char* name );

	template<typename CLASSNAME,typename PARENT1>
	luacpp::class_def<CLASSNAME> regClass ( const char* name );

    template<typename CLASSNAME>
    void regClassCreator ( );


    template<typename CLASSNAME, typename FUNC>
    void regClassFunction ( const char* name, FUNC fun );

	template<typename CLASSNAME, typename FUNC>
	void regClassStaticFunction ( const char* name, FUNC fun );
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

extern CXLuaScript gLuaScript;

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
template<typename CLASSNAME,typename PARENT>
luacpp::class_def<CLASSNAME> CXLuaScript::regClass ( const char* name )
{
	return luacpp::reg_cclass<CLASSNAME,PARENT>::_reg ( mState, name );
}
template<typename FUNC>
void CXLuaScript::regGlobalFun ( const char* name, FUNC fun )
{
    luacpp::reg_cfun ( mState, name, fun );
}

