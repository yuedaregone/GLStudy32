#include "Sprite.h"
#include "texture.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "LuaConfig.h"
#include "GLFilterMgr.h"

Sprite* Sprite::createWithBMP(const char* fileName)
{
	Sprite* pRet = new Sprite();
	if (pRet)
	{
		pRet->initWithBMP(fileName);
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

void Sprite::initWithBMP(const char* fileName)
{
	m_texture = loadBMP_custom(fileName, m_w, m_h);
	initVertex();
	initTextureCood();
	initMatrix();
}

void Sprite::setPosition(int x, int y)
{

}

void Sprite::setColor(float r, float g, float b, float a)
{

}

void Sprite::setOpacity(float opacity)
{

}

void Sprite::setScale(float s)
{

}

void Sprite::setScale(float sx, float sy)
{

}

void Sprite::setRotation(float degree)
{

}

void Sprite::initVertex()
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

void Sprite::initTextureCood()
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

void Sprite::initMatrix()
{
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

void Sprite::updateMatrix()
{
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
		float posX = (float)m_x * 2 / width - 1;
		float posY = (float)m_y * 2 / height - 1;
		glm::mat4 translateMatrix = glm::translate(temp, glm::vec3(posX, posY, 0.0f));
		//rotation
		glm::mat4 rotationMatrix = glm::rotate(temp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		m_mvp = m_vp*translateMatrix*rotationMatrix*scaleMatrix;
		m_isDirty = false;
	}
}

void Sprite::draw()
{
	updateMatrix();
	g_pFilterMgr->getDefaultFilter()->render(this);
}
