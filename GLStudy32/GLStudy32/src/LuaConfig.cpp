#include "LuaConfig.h"
#include <assert.h>

LuaConfig* LuaConfig::m_instance = NULL;

LuaConfig* LuaConfig::getInstance()
{
	if (m_instance == NULL)
		m_instance = new LuaConfig();
	return m_instance;
}

void LuaConfig::closeLua()
{
	if (m_L)
	{
		lua_close(m_L);
	}
}

void LuaConfig::initLua()
{
	m_L = luaL_newstate();
	if (luaL_loadfile(m_L, "./setting.lua") || lua_pcall(m_L, 0, 0, 0))
	{
		printf("LUA ERROR:%s", lua_tostring(m_L, -1));
		closeLua();
		m_L = NULL;
		return;
	}
}

void LuaConfig::getInfo(int& w, int& h, std::string& title)
{
	assert(m_L && "lua must be hava a value!");	

	lua_getglobal(m_L, "globle_info");
	lua_getfield(m_L, -1, "width");
	w = (int)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_getfield(m_L, -1, "height");
	h = (int)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_getfield(m_L, -1, "title");
	title = (char*)lua_tostring(m_L, -1);
	lua_pop(m_L, 1);
	lua_pop(m_L, 1);

	m_width = w;
	m_height = h;
}

void LuaConfig::getRGBA(float& r, float& g, float& b, float& a)
{
	assert(m_L && "lua must be hava a value!");

	lua_getglobal(m_L, "bg_color");
	lua_getfield(m_L, -1, "r");
	r = (float)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_getfield(m_L, -1, "g");
	g = (float)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_getfield(m_L, -1, "b");
	b = (float)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_getfield(m_L, -1, "a");
	a = (float)lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	lua_pop(m_L, 1);
}

std::string LuaConfig::getVertexStr()
{
	assert(m_L && "lua must be hava a value!");

	lua_getglobal(m_L, "getVertexShader");
	lua_pcall(m_L, 0, -1, 0);
	const char* temp = lua_tostring(m_L, -1);
	lua_pop(m_L, 1);
	return temp;
}

std::string LuaConfig::getFragmentStr()
{
	assert(m_L && "lua must be hava a value!");

	lua_getglobal(m_L, "getFragmentShader");
	lua_pcall(m_L, 0, -1, 0);
	const char* temp = lua_tostring(m_L, -1);
	lua_pop(m_L, 1);
	return temp;
}

int LuaConfig::getStackNum()
{
	assert(m_L && "lua must be hava a value!");

	return lua_gettop(m_L);
}

/************************************************************/

void LuaConfig::getWindowSize(int& w, int& h)
{
	if (m_width < 0 || m_height < 0)
	{
		if (isExit())
		{
			std::string temp;
			getInfo(w, h, temp);
		}
		else
		{
			w = m_width = 300;
			h = m_height = 300;
		}
	}
	else
	{
		w = m_width;
		h = m_height;
	}
}