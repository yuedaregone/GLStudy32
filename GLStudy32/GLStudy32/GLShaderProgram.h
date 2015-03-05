#ifndef __GLSHADERPROGRAM_H__
#define __GLSHADERPROGRAM_H__
#include "glew.h"
#include "GLSprite.h"
class GLShaderProgram
{
public:
	static GLShaderProgram* getShaderProgram();
	void shaderInit();
	void dataInit();
	void use();
private:
	GLuint m_programId;
	GLuint m_vertexPosition;
	GLuint m_MVP;
	GLuint m_UV;
	GLuint m_sampler;	
	static GLShaderProgram* m_instance;
	friend GLSprite;
};
#define g_pShaderProgram GLShaderProgram::getShaderProgram()
#endif