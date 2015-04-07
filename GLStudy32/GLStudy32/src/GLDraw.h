#ifndef __GL_DRAW__H__
#define __GL_DRAW__H__
#include <stdio.h>
#include <glm/glm.hpp>
class GLFilterSingle;
class GLDraw
{
public:
	GLDraw() :m_filter(NULL), m_drawColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), m_posSize(1.0f){};
	~GLDraw();
public:
	void initGLDraw();
	void setColor(float r, float g, float b, float a);
	void setPointSize(float _size);
	void drawPoint(int x, int y);	
private:
	GLFilterSingle* m_filter;
	glm::vec4 m_drawColor;
	glm::mat4 m_mvp;
	glm::mat4 m_vp;
	float m_posSize;
};



#endif