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
//#pragma comment(lib,"glew.lib")

class GlDraw
{
public:
	GlDraw() 
	{
		m_vetexId = 0;
	};
	~GlDraw() {};
	void drawInit()
	{		
		glGenBuffers(1, &m_vetexId);
		glBindBuffer(GL_ARRAY_BUFFER,m_vetexId);
		static const GLfloat g_vertex_buff_data[] = {
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
			0.0f, 0.8f, 0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data), g_vertex_buff_data, GL_STATIC_DRAW);	
	}
	void drawUpdate()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
private:
	GLuint m_vetexId;	
};

int main(void)
{
	if (!glfwInit()){			
		fprintf(stderr, "Failed to init glfw!");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	GLFWwindow* window = glfwCreateWindow(300, 300, "TEST", NULL, NULL);
	if (!window) {		
		fprintf(stderr, "Failed to create glfw window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to init glew!");	
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	GlDraw glDraw;
	glDraw.drawInit();
	
	bool isRun  = true;
	while (isRun) {
		glClear(GL_COLOR_BUFFER_BIT);		
		
		glDraw.drawUpdate();
		
		glfwSwapBuffers(window);
		isRun = GLFW_PRESS != glfwGetKey(window, GLFW_KEY_ESCAPE)
				&& !glfwWindowShouldClose(window);
		glfwPollEvents();
		Sleep(1);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
