#include "GLFilter.h"
#include "shader.h"
#include "Sprite.h"
#include <assert.h>

GLFilter::GLFilter()
	: m_iProgram(0)
	, m_vertexPosition(0)
	, m_MVP(0)
	, m_UV(0)
	, m_sampler(0)
	, m_colorEx(0)
	, m_reference(1)
{
}

void GLFilter::initFilter()
{
	m_iProgram = loadShaders(char_shader_texture_vertex, char_shader_texture_frag);
	initShaderVarible();
}

void GLFilter::retain()
{
	++m_reference;
}

void GLFilter::release()
{
	assert(m_reference > 0 && "m_reference is wrong!");
	--m_reference;
	if (m_reference <= 0)
	{
		delete this;
	}
}

void GLFilter::initShaderVarible()
{
	m_vertexPosition = glGetAttribLocation(m_iProgram, "vertexPosition_modelspace");
	m_MVP = glGetUniformLocation(m_iProgram, "MVP");
	m_UV = glGetAttribLocation(m_iProgram, "vertexUV");
	m_sampler = glGetUniformLocation(m_iProgram, "myTextureSampler");
	m_colorEx = glGetUniformLocation(m_iProgram, "frag_color");
}

void GLFilter::use()
{
	glUseProgram(m_iProgram);
}

void GLFilter::render(Sprite* _sp)
{
	glUniformMatrix4fv(m_MVP, 1, GL_FALSE, &_sp->m_mvp[0][0]);
	//set color
	glUniform4f(m_colorEx, _sp->m_color.r, _sp->m_color.g, _sp->m_color.b, _sp->m_color.a);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _sp->m_texture);
	glUniform1i(m_sampler, 0);

	glEnableVertexAttribArray(m_vertexPosition);
	glBindBuffer(GL_ARRAY_BUFFER, _sp->m_vertexId);
	glVertexAttribPointer(m_vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(m_UV);
	glBindBuffer(GL_ARRAY_BUFFER, _sp->m_textureCoodId);
	glVertexAttribPointer(m_UV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_UV);
	glDisableVertexAttribArray(m_vertexPosition);
}

/**********************************GLFilterGray**************************************/

void GLFilterGray::initFilter()
{
	m_iProgram = loadShaders(char_shader_texture_vertex, char_shader_texture_gray_frag);
	initShaderVarible();
}

/**********************************GLFilterSpark**************************************/

void GLFilterSpark::initFilter()
{
	m_iProgram = loadShaders(char_shader_texture_vertex, char_shader_texture_spark_frag);
	initShaderVarible();
	m_shaderWidth = glGetUniformLocation(m_iProgram, "width");
	m_shaderOffset = glGetUniformLocation(m_iProgram, "offset");
	m_shaderColor = glGetUniformLocation(m_iProgram, "u_color");
}

void GLFilterSpark::render(Sprite* _sp)
{
	glUniform1f(m_shaderWidth, m_width);
	glUniform1f(m_shaderOffset, m_offset);
	glUniform4f(m_shaderColor, m_sparkColor.r, m_sparkColor.g, m_sparkColor.b, m_sparkColor.a);
	GLFilter::render(_sp);
}

void GLFilterSpark::setSparkColor(float r, float g, float b)
{
	m_sparkColor = glm::vec4(r, g, b, 1.0f);
}

/**********************************GLFilterSingle**************************************/

void GLFilterSingle::initFilter()
{
	m_iProgram = loadShaders(char_shader_color_draw_vertex, char_shader_color_frag);
	m_vertexPosition = glGetAttribLocation(m_iProgram, "vertexPosition_modelspace");
	m_MVP = glGetUniformLocation(m_iProgram, "MVP");	
	m_colorEx = glGetUniformLocation(m_iProgram, "vertexColor");
	m_posSize = glGetUniformLocation(m_iProgram, "pointSize");
}