#ifndef __MDrawTextureBox_H__
#define __MDrawTextureBox_H__
#include "MGraphicsProtocol.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <gl/gl.h>
#include "MObjActionProtocol.h"

class MDrawTextureBox : public MGraphicsProtocol
{
public:
	MDrawTextureBox();
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
	MObjActionProtocol* m_objAction;
	glm::mat4 m_MVP;
};

#endif