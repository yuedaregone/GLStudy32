#include "GLShaderProgram.h"
#include "LuaConfig.h"
#include "shader.h"

GLShaderProgram* GLShaderProgram::m_instance = NULL;

GLShaderProgram* GLShaderProgram::getShaderProgram()
{
	if (!m_instance)
	{
		m_instance = new GLShaderProgram;
		m_instance->shaderInit();
		m_instance->dataInit();
	}		
	return m_instance;
}

void GLShaderProgram::shaderInit()
{
	if (g_pLuaConfig->isExit())
	{
		std::string vertex = g_pLuaConfig->getVertexStr();
		std::string fragment = g_pLuaConfig->getFragmentStr();
		if (!vertex.empty() && !fragment.empty())
		{
			m_programId = loadShaders(vertex.c_str(), fragment.c_str());
		}
	}
	else
	{
		const char* verStr = "\
			#version 120													\n\
			attribute vec3 vertexPosition_modelspace;						\n\
			attribute vec2 vertexUV;										\n\
			varying vec2 UV;												\n\
			uniform mat4 MVP;												\n\
			void main(){													\n\
				gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);		\n\
				UV = vertexUV;												\n\
			}																\n\
		";

		const char* fragStr = "\
			#version 120											\n\
			varying vec2 UV;										\n\
			uniform vec4 frag_color;								\n\
			uniform sampler2D myTextureSampler;						\n\
			void main(){											\n\
				vec4 texColor =	texture2D(myTextureSampler,UV);		\n\
				gl_FragColor = texColor*frag_color;					\n\
			}														\n\
		";	
		m_programId = loadShaders(verStr, fragStr);
	}
}

void GLShaderProgram::dataInit()
{
	m_vertexPosition = glGetAttribLocation(m_programId, "vertexPosition_modelspace");	
	m_MVP = glGetUniformLocation(m_programId, "MVP");
	m_UV = glGetAttribLocation(m_programId, "vertexUV");
	m_sampler = glGetUniformLocation(m_programId, "myTextureSampler");
	m_colorEx = glGetUniformLocation(m_programId, "frag_color");
}

void GLShaderProgram::use()
{
	glUseProgram(m_programId);
}
