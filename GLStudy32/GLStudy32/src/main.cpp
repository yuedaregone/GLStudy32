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
#include "LuaConfig.h"
#include "GLSprite.h"
#include "Sprite.h"
#include "GLFilter.h"
#include "pic.h"
#include "png.h"
#include "GLDraw.h"

void calculate_fps()
{
	static double pre_time = 0;
	static int frames = 0;

	++frames;
	double cur_time = glfwGetTime();
	double gap_time = cur_time - pre_time;
	if (gap_time > 1.0)
	{
		double fps = frames / gap_time;
		printf("%.1f\n", fps);
		frames = 0;
		pre_time = cur_time;
	}
}
//#pragma comment(lib,"glew.lib")
/************************************************************************/
/* glDraw																*/
/* create gl data:1.Generate buff 2.Bind buff 3.Set buff data			*/
/* update draw:1.Enable draw point 2.Bind buff 3.Set point property		*/
/*			   4.draw point 5.Disable draw point						*/
/************************************************************************/
//int _stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
int main(void)
{
	//init lua
	g_pLuaConfig->initLua();	

	int width = 300, height = 300;
	std::string title = "TEST";
	if (g_pLuaConfig->isExit())
		g_pLuaConfig->getInfo(width, height, title);

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
	glfwSetWindowPos(window, 0, 600);

	if (glewInit() != GLEW_OK) { //init glew
		fprintf(stderr, "Failed to init glew!");	
		return -1;
	}
	float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
	if (g_pLuaConfig->isExit())
		g_pLuaConfig->getRGBA(r, g, b, a);
	glClearColor(r, g, b, a); //set gl background color
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
		
	//MGraphicsProtocol* glDraw = new MDrawTextureBox(); //gl draw class
	//glDraw->shaderInit();
	//glDraw->drawInit();
	
	//GLSprite* sp = GLSprite::createWithBMP("texture.bmp", 100, 100);
	//sp->setPosition(150, 150);
	//sp->setOpacity(0.3f);
	//sp->setScale(0.5f, 1.0f);
	//sp->setRotation(90);

	//GLSprite* sp1 = GLSprite::createWithBMP("texture.bmp", 50, 50);
	//sp1->setPosition(25, 25);
	//sp1->setScale(1.5f, 2.0f);
	//sp1->setColor(1.0f, 0.0f, 1.0f, 1.0f);

	//Sprite* sp = Sprite::createWithBMP("texture.bmp");//createWithDDS("texture.dds");
	Sprite* sp = Sprite::createWithPNG("texture.png");
	sp->setPosition(150, 150);

	Sprite* sp0 = Sprite::createWithBMP("texture.bmp");
	sp0->setPosition(32, 268);
	sp0->setScale(0.5f);
	//sp0->setRotation(180.0f);

	GLFilterSpark* filter = new GLFilterSpark();
	filter->initFilter();	
	sp->setFilter(filter);
	sp0->setFilter(filter);


	Sprite* sp1 = Sprite::createWithData(ImageData::imgPic_1, false, 128, 128);
	sp1->setScale(0.5f);
	sp1->setPosition(32, 32);
	//sp1->setFilter(filter);

	GLDraw drawNode;
	drawNode.initGLDraw();
	drawNode.setColor(1.0f, 1.0f, 0.0f, 1.0f);
	drawNode.setPointSize(1.5f);
	
	float temp = -1.2f;

	double interval = 1.0f / 60;
	double lastTime = glfwGetTime();
	bool isRun  = true;
	while (isRun) { //gl draw main loop
		double nowTime = glfwGetTime();
		if (nowTime - lastTime < interval)
			continue;
		lastTime = nowTime;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color	
		
		//glDraw->actionUpdate();
		//glDraw->drawUpdate(); //gl draw update
		//sp->draw();
		//sp1->draw();
		drawNode.drawPoint(-10, -10);

		//filter->setSparkOffset(temp);		
		//sp->draw();
		//sp0->draw();
		//sp1->draw();
		if (temp > 1.2f)
		{
			temp = -1.2f;
		}
		else
		{
			temp = temp + 0.02f;
		}
		
		glfwSwapBuffers(window);
		isRun = GLFW_PRESS != glfwGetKey(window, GLFW_KEY_ESCAPE)
				&& !glfwWindowShouldClose(window);
		glfwPollEvents();
		calculate_fps();
		Sleep(1);
	}
	//delete glDraw;
	sp->release();
	g_pLuaConfig->closeLua();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
