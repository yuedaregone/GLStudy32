#ifndef __SPRITE_H__
#define __SPRITE_H__
#include "GLFilter.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


class Sprite
{
public:
    static Sprite* createWithBMP(const char* fileName);
    void initWithBMP(const char* fileName);
    void setPosition(int x, int y);
    void setColor(float r, float g, float b, float a = 1.0f);
    void setOpacity(float opacity);
    void setScale(float s);
    void setScale(float sx, float sy);
    void setRotation(float degree);
    void draw();
private:
    Sprite() :m_w(0), m_h(0), m_x(0), m_y(0), m_isDirty(true), m_scaleX(1.0f), m_scaleY(1.0f), m_rotation(0.0f){}
    ~Sprite() {}
private:
	void initVertex();
	void initTextureCood();
	void initMatrix();
	void updateMatrix();
private:
    unsigned int m_w;
	unsigned int m_h;
    int m_x;
    int m_y;
    float m_scaleX;
    float m_scaleY;
    float m_rotation;
    bool m_isDirty;
private:
	GLuint m_texture;
	GLuint m_vertexId;
	GLuint m_textureCoodId;	
	glm::mat4 m_mvp;
	glm::mat4 m_vp;
	glm::vec4 m_color;
	friend GLFilter;
};
#endif