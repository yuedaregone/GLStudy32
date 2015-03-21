#ifndef __SPRITE_H__
#define __SPRITE_H__
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
    int m_w;
    int m_h;
    int m_x;
    int m_y;
    float m_scaleX;
    float m_scaleY;
    float m_rotation;
    bool m_isDirty;
};
#endif