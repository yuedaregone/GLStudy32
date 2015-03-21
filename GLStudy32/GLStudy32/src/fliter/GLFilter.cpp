#include "GLFilter.h"
#include "shader.h"

GLFilter::GLFilter()
	: m_iProgram(0)
	, m_vertexPosition(0)
	, m_MVP(0)
	, m_UV(0)
	, m_sampler(0)
	, m_colorEx(0)
{
}

void GLFilter::initFilter()
{
	m_iProgram = loadShaders(char_shader_texture_vertex, char_shader_texture_frag);
	m_vertexPosition = glGetAttribLocation(m_iProgram, "vertexPosition_modelspace");
	m_MVP = glGetUniformLocation(m_iProgram, "MVP");
	m_UV = glGetAttribLocation(m_iProgram, "vertexUV");
	m_sampler = glGetUniformLocation(m_iProgram, "myTextureSampler");
	m_colorEx = glGetUniformLocation(m_iProgram, "frag_color");
}

void GLFilter::render(Sprite* _sp)
{
	glUniformMatrix4fv(m_MVP, 1, GL_FALSE, &_sp->m_mvp[0][0]);
	//set color
	glUniform4f(m_colorEx, m_color.r, m_color.g, m_color.b, m_color.a);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(g_pShaderProgram->m_sampler, 0);

	glEnableVertexAttribArray(g_pShaderProgram->m_vertexPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexId);
	glVertexAttribPointer(g_pShaderProgram->m_vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(g_pShaderProgram->m_UV);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoodId);
	glVertexAttribPointer(g_pShaderProgram->m_UV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(g_pShaderProgram->m_UV);
	glDisableVertexAttribArray(g_pShaderProgram->m_vertexPosition);
}