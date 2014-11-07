#ifndef _LUACOMMON_H
#define _LUACOMMON_H
#define LUA_COMPAT_MODULE
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
//namespace luacpp{
//
//	template<typename T>
//	class objPush;
//	template<typename T>
//	T popvalue(lua_State *L);	
//
//	template<typename T>
//	void push_obj(lua_State *L,const T &obj);
//}
#endif
