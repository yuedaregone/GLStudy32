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
#include <glm/glm.hpp>
#include "shader.h"
//#pragma comment(lib,"glew.lib")
/************************************************************************/
/* glDraw																*/
/* create gl data:1.Generate buff 2.Bind buff 3.Set buff data			*/
/* update draw:1.Enable draw point 2.Bind buff 3.Set point property		*/
/*			   4.draw point 5.Disable draw point						*/
/************************************************************************/
class GlDraw
{
public:
	GlDraw() 
	{
		m_vetexId = 0;
		m_vetexId1 = 0;
		m_programId = 0;
	};
	~GlDraw() {};
	void shaderInit()
	{
		const char* verStr = "\
			#version 120											\n\
			attribute vec3 vertexPosition_modelspace; \n\
			void main(){											\n\
				gl_Position = vec4(vertexPosition_modelspace, 1.0);	\n\
			}														\n\
		";

		const char* fragStr = "\
			void main(){						\n\
				gl_FragColor = vec4(0,0,1,0.4);	\n\
			}									\n\
		";
		m_programId = loadShaders(verStr, fragStr);
		m_vertexPos_modelspaceID = glGetAttribLocation(m_programId, "vertexPosition_modelspace");
	}
	void drawInit()
	{
		glGenBuffers(1, &m_vetexId);
		glBindBuffer(GL_ARRAY_BUFFER,m_vetexId);
		static const GLfloat g_vertex_buff_data[] = {
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
			0.0f, 0.8f, 0.0f,			
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data), g_vertex_buff_data, GL_STATIC_DRAW);


		glGenBuffers(1, &m_vetexId1);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		static const GLfloat g_vertex_buff_data1[] = {
			-0.8f, 0.8f, 0.0f,
			0.8f, 0.8f, 0.0f,
			0.0f, -0.8f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data1), g_vertex_buff_data1, GL_STATIC_DRAW);
	}
	void drawUpdate()
	{
		glUseProgram(m_programId);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(m_vertexPos_modelspaceID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId);
		glVertexAttribPointer(
			m_vertexPos_modelspaceID,// attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,					// size
			GL_FLOAT,			// type
			GL_FALSE,			// normalized?
			0,					// stride
			(void*)0);			// array buffer offset
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 1; 3 vertices total -&gt; 1 triangle		

		
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		glVertexAttribPointer(m_vertexPos_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(m_vertexPos_modelspaceID);
	}
private:
	GLuint m_vetexId;
	GLuint m_vetexId1;
	GLuint m_programId;
	GLuint m_vertexPos_modelspaceID;
};

int main(void)
{
	if (!glfwInit()){ //init glfw	
		fprintf(stderr, "Failed to init glfw!");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); //gl kang ju chi,u can input 2,4,8,the more big ,the effect more good
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	//create a openGL window
	GLFWwindow* window = glfwCreateWindow(300, 300, "TEST", NULL, NULL); 
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

	GlDraw glDraw; //gl draw class
	glDraw.shaderInit();
	glDraw.drawInit();
	
	bool isRun  = true;
	while (isRun) { //gl draw main loop
		glClear(GL_COLOR_BUFFER_BIT);	//clear color	
		
		glDraw.drawUpdate(); //gl draw update
		
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
