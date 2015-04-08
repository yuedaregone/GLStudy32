#ifndef __GLFILTER_H__
#define __GLFILTER_H__
#include <GL/glew.h>
#include "glm/glm.hpp"
class Sprite;
class GLFilterMgr;
class GLFilter
{
public:
	virtual void initFilter();	
	void use();
	virtual void render(Sprite* _sp);
	void retain();
	void release();
protected:
	GLFilter();
	virtual ~GLFilter() {}
protected:
	void initShaderVarible();
protected:
	GLint m_iProgram;
	GLint m_vertexPosition;
	GLint m_MVP;
	GLint m_UV;
	GLint m_sampler;
	GLint m_colorEx;	
private:
	unsigned int m_reference;
	friend class GLFilterMgr;
};

class GLFilterGray :public GLFilter
{
public:
	virtual void initFilter();	
protected:
	GLFilterGray() :GLFilter() {};
	~GLFilterGray() {}
};

class GLFilterSpark :public GLFilter
{
public:
	virtual void initFilter();
	virtual void render(Sprite* _sp);
	void setSparkWidth(float _w) { m_width = _w; }
	void setSparkOffset(float _offset) { m_offset = _offset; }
	float getSparkWidth() { return m_width; }
	float getSparkOffset() { return m_offset; }
	void setSparkColor(float r, float g, float b);
protected:
	GLFilterSpark() :GLFilter(), m_width(0.2f), m_offset(0.0f), m_sparkColor(glm::vec4(1.0)){};
	~GLFilterSpark() {}
private:
	GLint m_shaderWidth;
	GLint m_shaderOffset;
	GLint m_shaderColor;
	float m_width; //spark width
	float m_offset; //spark offset
	glm::vec4 m_sparkColor;
};

class GLFilterUV :public GLFilter
{
public:
	virtual void initFilter();
	virtual void render(Sprite* _sp);
	void setUVOffset(float _offset);
public:
	GLFilterUV() :GLFilter(), m_uvOffset(0.0f){};
	~GLFilterUV() {}
private:
	GLint m_uvOffsetLoc;
	float m_uvOffset;
};

class GLFilterSingle : public GLFilter
{
public:
	virtual void initFilter();
	GLint getVertexPositionLoc() { return m_vertexPosition; }
	GLint getMVPLoc() { return m_MVP; }
	GLint getColorLoc() { return m_colorEx; }
	GLint getPosSizeLoc() { return m_posSize; }
public:
	GLFilterSingle() :GLFilter(){}
	~GLFilterSingle() {}
private:
	GLint m_posSize;	
};

#endif