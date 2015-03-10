#ifndef __GLSPRITE_H__
#define __GLSPRITE_H__
#include <GL/glew.h>
#include <glm/glm.hpp>

class GLSprite
{
public:
	static GLSprite* createWithBMP(const char* file, int w, int h);
	void initWithBMP(const char* file, int w, int h);
	void setPosition(int x, int y);
	void setColor(float r, float g, float b);
	void draw();
private:
	GLSprite() :m_w(0), m_h(0), m_x(0), m_y(0), m_isDirty(true){}
	~GLSprite() {}
	void release();
	void initVertex();
	void initTextureCood();	
	void initMatrix();
	void updateMatrix();
private:
	int m_w;
	int m_h;
	int m_x;
	int m_y;
	GLuint m_texture;
	GLuint m_vertexId;
	GLuint m_textureCoodId;
	GLuint m_vao;
	glm::mat4 m_mvp;
	glm::mat4 m_vp;
	glm::vec4 m_color;
	bool m_isDirty;
};



#endif