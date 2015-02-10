/**
	File Name: main.cpp
	Description: just study opengl
	Created by yue
*/

#include <windows.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <gl/gl.h>
#include "MDrawColorBox.h"
#include "MDrawTextureBox.h"
#include "lua.hpp"
#include <string>

//#pragma comment(lib,"glew.lib")
/************************************************************************/
/* glDraw																*/
/* create gl data:1.Generate buff 2.Bind buff 3.Set buff data			*/
/* update draw:1.Enable draw point 2.Bind buff 3.Set point property		*/
/*			   4.draw point 5.Disable draw point						*/
/************************************************************************/
lua_State* L = NULL;
void closeLua()
{
	if (L)
	{
		lua_close(L);
	}
}

void initLua()
{
	L = luaL_newstate();
	if (luaL_loadfile(L, "./setting.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("LUA ERROR:%s", lua_tostring(L, -1));
		closeLua();
		L = NULL;
		return;
	}
}

void getInfo(int& w, int& h, std::string& title)
{
	if (!L)
		return;
	
	lua_getglobal(L, "globle_info");	
	lua_getfield(L, -1, "width");
	w = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, -1, "height");
	h = (int)lua_tonumber(L, -1);	
	lua_pop(L, 1);
	lua_getfield(L, -1, "title");
	title = (char*)lua_tostring(L, -1);
	lua_pop(L, 1);	
	lua_pop(L, 1);
}

//int _stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
int main(void)
{
	//init lua
	initLua();
	int width = 300, height = 300;
	std::string title = "TEST";
	getInfo(width, height, title);

	if (!glfwInit()){ //init glfw	
		fprintf(stderr, "Failed to init glfw!");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); //gl kang ju chi,u can input 2,4,8,the more big ,the effect more good
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	//create a openGL window
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {		
		fprintf(stderr, "Failed to create glfw window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //set the openGL context

	if (glewInit() != GLEW_OK) { //init glew
		fprintf(stderr, "Failed to init glew!");	
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set gl background color
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	MGraphicsProtocol* glDraw = new MDrawTextureBox(); //gl draw class
	glDraw->shaderInit();
	glDraw->drawInit();
	
	bool isRun  = true;
	while (isRun) { //gl draw main loop
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color	
		
		glDraw->actionUpdate();
		glDraw->drawUpdate(); //gl draw update
		
		glfwSwapBuffers(window);
		isRun = GLFW_PRESS != glfwGetKey(window, GLFW_KEY_ESCAPE)
				&& !glfwWindowShouldClose(window);
		glfwPollEvents();
		Sleep(1);
	}
	delete glDraw;
	closeLua();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
