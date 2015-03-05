#ifndef __LUACONFIG_H__
#define __LUACONFIG_H__
#include "lua.hpp"
#include <string>
class LuaConfig
{
public:	
	static LuaConfig* getInstance();
	void closeLua();
	void initLua();
	bool isExit() { return m_L != NULL; }
	void getInfo(int& w, int& h, std::string& title);
	void getRGBA(float& r, float& g, float& b, float& a);
	std::string getVertexStr();
	std::string getFragmentStr();
	int getStackNum();
public:
	void getWindowSize(int& w, int& h);
private:
	LuaConfig() : m_L(NULL), m_width(-1), m_height(-1){}
	lua_State* m_L;
	static LuaConfig* m_instance;
private:
	int m_width;
	int m_height;
};

#define g_pLuaConfig LuaConfig::getInstance()
#endif