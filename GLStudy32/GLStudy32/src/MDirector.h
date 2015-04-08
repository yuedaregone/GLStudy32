#ifndef _MDIRECTOR_H__
#define _MDIRECTOR_H__
#include "MSingleton.h"
class MDirector
{
public:
	MDirector();
public:
	void init();
	void mainLoop();
	void destroy();
private:
	bool m_isPause;
};
#define g_pDirector MSingleton<MDirector>::getInstance()
#endif