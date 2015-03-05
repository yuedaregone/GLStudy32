#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "texture.hpp"
#include "pic.h"
#include "MDrawColorBox.h"
#include "MActionSimple.h"

MDrawColorBox::MDrawColorBox()
{
	m_vetexId = 0;
	m_vetexId1 = 0;
	m_programId = 0;
	m_objAction = new MActionSimple();
};

void MDrawColorBox::shaderInit()
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
	m_programId = loadShaders(verStr, fragStr);
	m_vertexPos_modelspaceID = glGetAttribLocation(m_programId, "vertexPosition_modelspace");
	m_matrixId = glGetUniformLocation(m_programId, "MVP");
	m_colorId = glGetAttribLocation(m_programId, "vertexColor");
	//create MVP
	m_objAction->initMatrix();
}
void MDrawColorBox::drawInit()
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
void MDrawColorBox::drawUpdate()
{		
	glUseProgram(m_programId);
				
	m_MVP = m_objAction->getMVP();
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
}