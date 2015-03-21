#include "GLSprite.h"
#include <stdio.h>
#include "texture.hpp"
#include "GLShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include "LuaConfig.h"
#include "shader.h"

GLSprite* GLSprite::createWithBMP(const char* file, int w, int h)
{
	GLSprite* pRet = new GLSprite();
	if (pRet)
	{
		pRet->initWithBMP(file, w, h);
	}
	else 
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

void GLSprite::initWithBMP(const char* file, int w, int h)
{
	m_w = w;
	m_h = h;
	m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_pShaderProgram;
	m_texture = loadBMP_custom(file, m_w, m_h);	
	initVertex();
	initTextureCood();
	initMatrix();
}

void GLSprite::initVertex()
{
	glGenBuffers(1, &m_vertexId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexId);
	static const GLfloat g_vertex_data[] = {
		-1.0f, 1.0f, 1.0f, //front
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, //front end		
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_data), g_vertex_data, GL_STATIC_DRAW);
}

void GLSprite::initTextureCood()
{
	glGenBuffers(1, &m_textureCoodId);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoodId);
	static const GLfloat g_texture_cood[] = {
		0.000000f, 1.000000f,
		0.000000f, 0.000000f,
		1.000000f, 0.000000f,
		1.000000f, 1.000000f,
		0.000000f, 1.000000f,
		1.000000f, 0.000000f		
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_texture_cood), g_texture_cood, GL_STATIC_DRAW);
}

void GLSprite::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	m_isDirty = true;
}

void GLSprite::setColor(float r, float g, float b, float a)
{
	m_color = glm::vec4(r*a, g*a, b*a, a);
}

void GLSprite::setOpacity(float opacity)
{
	float a = m_color.a;
	m_color = glm::vec4(m_color.r / a*opacity, m_color.g / a*opacity, m_color.b / a*opacity, opacity);
}

void GLSprite::setScale(float s)
{
	m_scaleX = m_scaleY = s;
	m_isDirty = true;
}

void GLSprite::setScale(float sx, float sy)
{
	m_scaleX = sx;
	m_scaleY = sy;
	m_isDirty = true;
}

void GLSprite::setRotation(float degree)
{
	m_rotation = degree / 180 * glm::pi<float>();
}

void GLSprite::draw()
{
	g_pShaderProgram->use();

	updateMatrix();
	glUniformMatrix4fv(g_pShaderProgram->m_MVP, 1, GL_FALSE, &m_mvp[0][0]);
	//set color
	glUniform4f(g_pShaderProgram->m_colorEx, m_color.r, m_color.g, m_color.b, m_color.a);	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(g_pShaderProgram->m_sampler, 0);

	glEnableVertexAttribArray(g_pShaderProgram->m_vertexPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexId);
	glVertexAttribPointer(g_pShaderProgram->m_vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(g_pShaderProgram->m_UV);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoodId);
	glVertexAttribPointer(g_pShaderProgram->m_UV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(g_pShaderProgram->m_UV);
	glDisableVertexAttribArray(g_pShaderProgram->m_vertexPosition);
}

void GLSprite::initMatrix()
{	
	//in fact, only model matrix
	int width = 0, height = 0;
	g_pLuaConfig->getWindowSize(width, height);
	glm::mat4 projection = glm::perspective(90.0f, (GLfloat)width / height, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 1.61f), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	m_vp = projection*View;
	m_mvp = glm::mat4(1.0f);
}

void GLSprite::updateMatrix()
{
	//glm::mat4 projection = glm::perspective(45.0f, 1.0f / 1.0f, 0.1f, 100.0f);
	//glm::mat4 View = glm::lookAt(
	//	glm::vec3(0, 0, 6), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//	);	
	//Model = glm::rotate(Model, 0.001f, glm::vec3(1, 1, 1));
	//m_mvp = projection*View*Model;
	if (m_isDirty)
	{
		glm::mat4 temp = glm::mat4(1.0f);
		//scale
		int width = 0, height = 0;
		g_pLuaConfig->getWindowSize(width, height);
		float scaleX = (float)m_w / width * m_scaleX;
		float scaleY = (float)m_h / height * m_scaleY;
		glm::mat4 scaleMatrix = glm::scale(temp, glm::vec3(scaleX, scaleY, 1.0f));
		//position
		float posX = (float)m_x*2  / width - 1;
		float posY = (float)m_y*2  / height - 1;
		glm::mat4 translateMatrix = glm::translate(temp, glm::vec3(posX, posY, 0.0f));
		//rotation
		glm::mat4 rotationMatrix = glm::rotate(temp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		m_mvp = m_vp*translateMatrix*rotationMatrix*scaleMatrix;
		m_isDirty = false;
	}
}

void GLSprite::release()
{
	delete this;
}