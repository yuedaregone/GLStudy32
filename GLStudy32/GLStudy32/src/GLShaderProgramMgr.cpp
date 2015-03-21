#include "GLShaderProgramMgr.h"
#include <stdio.h>
GLShaderProgramMgr* GLShaderProgramMgr::m_instance = NULL;

GLShaderProgramMgr* GLShaderProgramMgr::getShaderMgr()
{
	if (!m_instance)
	{
		m_instance = new GLShaderProgramMgr;
	}
	return m_instance;
}