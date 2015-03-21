#ifndef __GLFILTER_H__
#define __GLFILTER_H__
#include <GL/glew.h>
#include "Sprite.h"

class GLFilter
{
public:
	void initFilter();	
	void render(Sprite* _sp);
public:
	GLFilter();
	virtual ~GLFilter() {}
protected:
	GLuint m_iProgram;
	GLuint m_vertexPosition;
	GLuint m_MVP;
	GLuint m_UV;
	GLuint m_sampler;
	GLuint m_colorEx;
};

#endif