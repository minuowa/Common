/*	
Copyright (C) <2012>  <huangweilook@21cn.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/	
#ifndef _LUAWRAPPER_H
#define _LUAWRAPPER_H

#pragma once 
#include "luacommon.h"
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "luaObject.h"
#include "luaClass.h"
#include "PopValue.h"
#include "ObjPush.h"
#include "lua.h"
#include "..\base.h"
namespace luacpp{

	class luaWrapper
	{	   
	public:
		operator lua_State* ()
		{
			return lState;
		}

		void init();
		luaWrapper(){init();}
		~luaWrapper()
		{
			if(lState)
				lua_close(lState);
			lState = NULL;
		}

		bool dofile(const char *filename);

	private:
		lua_State *lState;
	};

	inline bool luaWrapper::dofile(const char *filename)
	{
		if (luaL_dofile(lState, filename)) {
			const char * error = lua_tostring(lState, -1);
			lua_pop(lState,1);
			printf("%s\n",error);
			return false;
		}
		return true;
	}

	static void kennyluainit(lua_State *L)
	{			
		luaL_newmetatable(L, "kenny.lualib");
		lua_pop(L,1);
	}

	inline void luaWrapper::init()
	{
		lState = luaL_newstate();
		luaL_openlibs(lState);
		kennyluainit(lState);
		Integer64::Register2Lua(lState);
	}

	inline int NewObj(lua_State *L,const void *ptr,const char *classname) 
	{
		size_t nbytes = sizeof(objUserData<void>);
		objUserData<void> *obj = (objUserData<void> *)lua_newuserdata(L, nbytes);
		obj->ptr = const_cast<void*>(ptr);
		obj->m_flag = 0x1234AFEC;
		obj->construct_by_lua = false;
		luaL_getmetatable(L, "kenny.lualib");
		lua_pushstring(L,classname);
		lua_gettable(L,-2);
		lua_setmetatable(L, -3);
		lua_pop(L,1);//pop mt kenny.lualib
		return 1;
	}

	inline int newI64(lua_State *L)
	{
		Integer64 *tmp = (Integer64*)lua_touserdata(L,2);
		if(tmp)
			lua_pushlightuserdata(L,tmp);
		else
		{
			long initval = (long)lua_tonumber(L,2);
			size_t nbytes = sizeof(Integer64);
			void *buf = lua_newuserdata(L, nbytes);
			new(buf)Integer64(initval);
		}
		Integer64::setmetatable(L);
		return 1;
	}

	inline void Integer64::Register2Lua(lua_State *L)
	{
		static const struct luaL_Reg i64Lib[] = {
			{"new",newI64},
			{NULL,NULL},
		};

		luaL_getmetatable(L, "kenny.lualib");
		lua_pushstring(L,"int64");
		lua_newtable(L);

		lua_pushstring(L, "__add");
		lua_pushcfunction(L, i64Add);
		lua_rawset(L, -3);

		lua_pushstring(L, "__sub");
		lua_pushcfunction(L, i64Sub);
		lua_rawset(L, -3);

		lua_pushstring(L, "__div");
		lua_pushcfunction(L, i64Div);
		lua_rawset(L, -3); 

		lua_pushstring(L, "__mul");
		lua_pushcfunction(L, i64Mul);
		lua_rawset(L, -3); 

		lua_pushstring(L, "__mod");
		lua_pushcfunction(L, i64Mod);
		lua_rawset(L, -3);

		lua_pushstring(L, "__eq");
		lua_pushcfunction(L, i64Eq);
		lua_rawset(L, -3);

		lua_pushstring(L, "__lt");
		lua_pushcfunction(L, i64Lt);
		lua_rawset(L, -3);

		lua_pushstring(L, "__le");
		lua_pushcfunction(L, i64Le);
		lua_rawset(L, -3);

		lua_pushstring(L, "__tostring");
		lua_pushcfunction(L, i64toString);
		lua_rawset(L, -3);

		//just for test
		lua_pushstring(L,"__gc");
		lua_pushcfunction(L, i64Destroy);
		lua_rawset(L, -3);

		lua_rawset(L,1);
		lua_pop(L,1);
		luaL_register(L,"i64",i64Lib);
		lua_pop(L,1);

	}

	inline void get_luatable(luatable &lt,lua_State *L)
	{
		lt = popvalue<luatable>(L);
	}
}

#endif