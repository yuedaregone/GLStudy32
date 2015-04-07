#include "GLDraw.h"
#include "GLFilter.h"
#include "GLFilterMgr.h"
#include <glm/gtc/matrix_transform.hpp>
#include "LuaConfig.h"

void GLDraw::initGLDraw()
{
	if (!m_filter)
	{
		m_filter = new GLFilterSingle();
		m_filter->initFilter();

		glEnable(GL_PROGRAM_POINT_SIZE);
		int width = 0, height = 0;
		g_pLuaConfig->getWindowSize(width, height);
		glm::mat4 projection = glm::perspective(90.0f, (GLfloat)width / height, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(
			glm::vec3(0, 0, 1.61f), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		m_vp = projection*View;
		m_mvp = m_vp;
	}	
}

void GLDraw::setColor(float r, float g, float b, float a)
{
	m_drawColor = glm::vec4(r*a, g*a, b*a, a);
}

void GLDraw::setPointSize(float _size)
{
	m_posSize = _size;
}

GLDraw::~GLDraw() 
{
	delete m_filter;
}

void GLDraw::drawPoint(int x, int y)
{
	initGLDraw();
	m_filter->use();	
	int w, h;
	g_pLuaConfig->getWindowSize(w, h);
	float pos[2] = { (float)x/w, (float)y/h};
	glUniformMatrix4fv(m_filter->getMVPLoc(), 1, GL_FALSE, &m_mvp[0][0]);
	//set size
	glUniform1f(m_filter->getPosSizeLoc(), m_posSize);
	//set color
	glUniform4f(m_filter->getColorLoc(), m_drawColor.r, m_drawColor.g, m_drawColor.b, m_drawColor.a);

	GLint _verPos = m_filter->getVertexPositionLoc();	
	glVertexAttribPointer(_verPos, 2, GL_FLOAT, GL_FALSE, 0, pos);
	glDrawArrays(GL_POINTS, 0, 1);
}