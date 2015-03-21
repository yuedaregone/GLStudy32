#include "GLFilterMgr.h"
#include "shader.h"

GLFilterMgr* GLFilterMgr::m_instance = NULL;

GLFilterMgr* GLFilterMgr::getInstance()
{
	if (!m_instance)
	{
		m_instance = new GLFilterMgr();
		m_instance->m_defaultFilter = new GLFilter();
		m_instance->m_defaultFilter->initFilter();
		m_instance->addFilter(e_fliter_default, m_instance->m_defaultFilter);
	}
	return m_instance;
}

GLFilter* GLFilterMgr::getFilterByType(FilterType _type)
{
	std::map<FilterType, GLFilter*>::iterator it = m_fliters.begin();
	if (it != m_fliters.end())
	{
		return it->second;
	}

}

void GLFilterMgr::addFilter(FilterType _type, GLFilter* _filter)
{
	if (m_fliters.find(_type) == m_fliters.end())
	{		
		m_fliters[_type] = _filter;			
	}
	else
	{
		if (m_fliters[_type] != _filter)
		{
			delete m_fliters[_type];
			m_fliters[_type] = _filter;
		}
	}
}

GLFilter* GLFilterMgr::getDefaultFilter()
{
	return m_defaultFilter;
}

void GLFilterMgr::setDefaultFilter(FilterType _type)
{
	if (m_fliters.find(_type) != m_fliters.end())
	{
		m_defaultFilter = m_fliters[_type];
	}	
}