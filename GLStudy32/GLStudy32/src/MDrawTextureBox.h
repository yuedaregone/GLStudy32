#ifndef __MDrawTextureBox_H__
#define __MDrawTextureBox_H__
#include "MGraphicsProtocol.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <gl/gl.h>

class MDrawTextureBox : public MGraphicsProtocol
{
public:
	MDrawTextureBox()
	{
		m_vetexId = 0;
		m_vetexId1 = 0;
		m_programId = 0;
	};
	~MDrawTextureBox() {};
	virtual void shaderInit();
	virtual void drawInit();	
	virtual void actionUpdate();	
	virtual void drawUpdate();	
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
};

#endif