#ifndef __GLFLITERMGR_H__
#define __GLFLITERMGR_H__
#include <map>
#include "GLFilter.h"

typedef enum _FilterType
{
	e_fliter_default,
	e_fliter_gray,
	e_fliter_spark,
	e_fliter_uv,
	e_fliter_blur,
	e_fliter_unknow
}FilterType;

class GLFilterMgr
{
public:
	static GLFilterMgr* getInstance();
	GLFilter* getFilterByType(FilterType _type);
	void addFilter(FilterType _type, GLFilter* _filter);
	GLFilter* getDefaultFilter();
	void setDefaultFilter(FilterType _type);
private:
	GLFilterMgr() {}
	~GLFilterMgr() {}
	//GLuint getFilterProgramByType(FilterType _type);
private:
	static GLFilterMgr* m_instance;
	std::map<FilterType, GLFilter*> m_fliters;
	GLFilter* m_defaultFilter;
};

#define g_pFilterMgr GLFilterMgr::getInstance()
#endif