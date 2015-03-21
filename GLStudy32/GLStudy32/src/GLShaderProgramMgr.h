#ifndef __GLSHADERPROGRAMMGR_H__
#define __GLSHADERPROGRAMMGR_H__
#include <map>
#include <string>
class GLShader
{
	GLShader();
	~GLShader();
};

class GLShaderProgramMgr
{
public:
	static GLShaderProgramMgr* getShaderMgr();
private:
	static GLShaderProgramMgr* m_instance;
	std::map<std::string, GLShader*> m_shaders;
};
#define g_pShaderMgr GLShaderProgramMgr::getShaderMgr()
#endif