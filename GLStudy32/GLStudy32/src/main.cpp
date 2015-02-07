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
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "texture.hpp"
#include "pic_sb.h"
#include "pic.h"
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
			#version 120													\n\
			attribute vec3 vertexPosition_modelspace;						\n\
			attribute vec3 vertexColor;										\n\
			varying vec3 fragmentColor;										\n\
			uniform mat4 MVP;												\n\
			void main(){													\n\
				gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);		\n\
				fragmentColor = vertexColor;								\n\
			}																\n\
		";

		const char* fragStr = "\
			#version 120									\n\
			varying vec3 fragmentColor;						\n\
			void main(){									\n\
				gl_FragColor = vec4(fragmentColor,1);		\n\
			}												\n\
		";

		/*const char* fragStr1 = "\
			void main(){						\n\
				gl_FragColor = vec4(1,0,0,0.4);	\n\
			}									\n\
		";*/
		m_programId = loadShaders(verStr, fragStr);
		m_vertexPos_modelspaceID = glGetAttribLocation(m_programId, "vertexPosition_modelspace");
		m_matrixId = glGetUniformLocation(m_programId, "MVP");
		m_colorId = glGetAttribLocation(m_programId, "vertexColor");
		//create MVP
		projection = glm::perspective(45.0f, 1.0f/1.0f, 0.1f, 100.0f);
		View = glm::lookAt(
			glm::vec3(0, 0, 6), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		Model = glm::mat4(1.0f);		
		/*m_programId1 = loadShaders(verStr, fragStr1);
		m_vertexPos_modelspaceID1 = glGetAttribLocation(m_programId1, "vertexPosition_modelspace");*/
	}
	void drawInit()
	{
		glGenBuffers(1, &m_vetexId);
		glBindBuffer(GL_ARRAY_BUFFER,m_vetexId);
		static const GLfloat g_vertex_buff_data[] = {
			-1.0f, -1.0f, -1.0f, // triangle 1 : begin
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, // triangle 1 : end
			1.0f, 1.0f, -1.0f, // triangle 2 : begin
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, // triangle 2 : end
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data), g_vertex_buff_data, GL_STATIC_DRAW);

		
		glGenBuffers(1, &m_vetexId1);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		GLfloat g_vertex_buff_data1[] = {
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,

			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,

			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,

			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,

			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,

			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
			0.8f, 0.0f, 0.0f,
			0.0f, 0.8f, 0.0f,
			0.0f, 0.0f, 0.8f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data1), g_vertex_buff_data1, GL_STATIC_DRAW);
	}
	void drawUpdate()
	{		
		glUseProgram(m_programId);
				
		Model = glm::rotate(Model, 0.01f, glm::vec3(1, 1, 1));
		//Model = glm::translate(Model, glm::vec3(0.01f, 0, 0));		
		m_MVP = projection*View*Model;
		glUniformMatrix4fv(m_matrixId, 1, GL_FALSE, &m_MVP[0][0]);
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
		//set color property
		glEnableVertexAttribArray(m_colorId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		glVertexAttribPointer(m_colorId, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 1; 3 vertices total -&gt; 1 triangle
		glDisableVertexAttribArray(m_colorId);
		glDisableVertexAttribArray(m_vertexPos_modelspaceID);

		/*glUseProgram(m_programId1);
		glEnableVertexAttribArray(m_vertexPos_modelspaceID1);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		glVertexAttribPointer(m_vertexPos_modelspaceID1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(m_vertexPos_modelspaceID1);	*/	
	}
private:
	GLuint m_vetexId;
	GLuint m_vetexId1;
	GLuint m_programId;
	GLuint m_vertexPos_modelspaceID;
	GLuint m_matrixId;
	GLuint m_colorId;
	glm::mat4 projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 m_MVP;
	/*GLuint m_programId1;
	GLuint m_vertexPos_modelspaceID1;*/
};

class GlDrawTexture
{
public:
	GlDrawTexture()
	{
		m_vetexId = 0;
		m_vetexId1 = 0;
		m_programId = 0;
	};
	~GlDrawTexture() {};
	void shaderInit()
	{
		const char* verStr = "\
			#version 120													\n\
			attribute vec3 vertexPosition_modelspace;						\n\
			attribute vec2 vertexUV;										\n\
			varying vec2 UV;												\n\
			uniform mat4 MVP;												\n\
			void main(){													\n\
				gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);		\n\
				UV = vertexUV;												\n\
			}																\n\
		";

		const char* fragStr = "\
			#version 120											\n\
			varying vec2 UV;										\n\
			uniform sampler2D myTextureSampler;						\n\
			void main(){											\n\
				gl_FragColor = texture2D(myTextureSampler,UV);		\n\
			}														\n\
		";		
		m_programId = loadShaders(verStr, fragStr);
		m_vertexPos_modelspaceID = glGetAttribLocation(m_programId, "vertexPosition_modelspace");
		m_matrixId = glGetUniformLocation(m_programId, "MVP");
		m_colorId = glGetAttribLocation(m_programId, "vertexUV");
		//add texture
		//m_texture = loadDDS("texture.dds");
		m_texture = loadData(ImageData::imgPic_1, sizeof(ImageData::imgPic_1), 128, 128);
		m_textureID = glGetUniformLocation(m_programId, "myTextureSampler");

		//create MVP
		projection = glm::perspective(45.0f, 1.0f/1.0f, 0.1f, 100.0f);
		View = glm::lookAt(
			glm::vec3(0, 0, 6), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		Model = glm::mat4(1.0f);		
	}
	void drawInit()
	{
		glGenBuffers(1, &m_vetexId);
		glBindBuffer(GL_ARRAY_BUFFER,m_vetexId);
		static const GLfloat g_vertex_buff_data[] = {	
			-1.0f, 1.0f, 1.0f, //front
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, //front end
			1.0f, 1.0f, -1.0f, //back
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f, 
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, //back end
			-1.0f, -1.0f, -1.0f, // left
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, // left end	
			1.0f, 1.0f, 1.0f, //right
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, //right end
			1.0f, -1.0f, 1.0f, //down
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,				
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, //down end		
			1.0f, 1.0f, 1.0f, //up
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f	//up end	
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data), g_vertex_buff_data, GL_STATIC_DRAW);

		
		glGenBuffers(1, &m_vetexId1);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		GLfloat g_vertex_buff_data1[] = {	
			0.000000f, 0.000000f,
			0.000000f, 1.000000f,
			1.000000f, 1.000000f,
			1.000000f, 0.000000f,
			0.000000f, 0.000000f,
			1.000000f, 1.000000f,
			1.000000f, 0.000000f,
			1.000000f, 1.000000f,
			0.000000f, 1.000000f,
			1.000000f, 0.000000f,
			0.000000f, 1.000000f,
			0.000000f, 0.000000f,
			0.000000f, 1.000000f,
			1.000000f, 1.000000f,
			1.000000f, 0.000000f,
			0.000000f, 1.000000f,			
			1.000000f, 0.000000f,
			0.000000f, 0.000000f,
			0.000000f, 0.000000f,
			1.000000f, 1.000000f,
			1.000000f, 0.000000f,
			1.000000f, 1.000000f,
			0.000000f, 0.000000f,
			0.000000f, 1.000000f,
			1.000000f, 1.000000f,
			0.000000f, 0.000000f,
			1.000000f, 0.000000f,
			1.000000f, 1.000000f,
			0.000000f, 1.000000f,
			0.000000f, 0.000000f,
			1.000000f, 1.000000f,
			1.000000f, 0.000000f,
			0.000000f, 0.000000f,
			1.000000f, 1.000000f,
			0.000000f, 0.000000f,
			0.000000f, 1.000000f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buff_data1), g_vertex_buff_data1, GL_STATIC_DRAW);

		m_MVP = projection*View*Model;
	}
	void actionUpdate()
	{
		//return;
		Model = glm::rotate(Model, 0.001f, glm::vec3(1, 1, 1));
		//Model = glm::translate(Model, glm::vec3(0.01f, 0, 0));		
		m_MVP = projection*View*Model;
	}
	void drawUpdate()
	{		
		glUseProgram(m_programId);			
		
		glUniformMatrix4fv(m_matrixId, 1, GL_FALSE, &m_MVP[0][0]);

		//get texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(m_textureID, 0);

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
		//set color property
		glEnableVertexAttribArray(m_colorId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vetexId1);
		glVertexAttribPointer(m_colorId, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 1; 3 vertices total -&gt; 1 triangle
		glDisableVertexAttribArray(m_colorId);
		glDisableVertexAttribArray(m_vertexPos_modelspaceID);	
	}
private:
	GLuint m_vetexId;
	GLuint m_vetexId1;
	GLuint m_programId;
	GLuint m_vertexPos_modelspaceID;
	GLuint m_matrixId;
	GLuint m_colorId;
	GLuint m_texture;
	GLuint m_textureID;
	glm::mat4 projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 m_MVP;
	/*GLuint m_programId1;
	GLuint m_vertexPos_modelspaceID1;*/
};

int _stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
//int main(void)
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	GlDrawTexture glDraw; //gl draw class
	glDraw.shaderInit();
	glDraw.drawInit();
	
	bool isRun  = true;
	while (isRun) { //gl draw main loop
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color	
		
		glDraw.actionUpdate();
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
