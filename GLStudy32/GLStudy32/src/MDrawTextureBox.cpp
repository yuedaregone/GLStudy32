#include "shader.h"
#include "texture.hpp"
#include "pic.h"
#include "MDrawTextureBox.h"
#include "MActionSimple.h"

MDrawTextureBox::MDrawTextureBox()
{
	m_vetexId = 0;
	m_vetexId1 = 0;
	m_programId = 0;
	m_objAction = new MActionSimple();
};

void MDrawTextureBox::shaderInit()
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
		m_texture = loadBMP_custom("texture.bmp");
		//m_texture = loadDDS("texture.dds");
		//m_texture = loadData(ImageData::imgPic_1, sizeof(ImageData::imgPic_1), 128, 128);
		m_textureID = glGetUniformLocation(m_programId, "myTextureSampler");

		//create MVP
		m_objAction->initMatrix();
}

void MDrawTextureBox::drawInit()
{
	glGenBuffers(1, &m_vetexId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vetexId);
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
}

void MDrawTextureBox::actionUpdate()
{
	//return;
	m_MVP = m_objAction->getMVP();
}

void MDrawTextureBox::drawUpdate()
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