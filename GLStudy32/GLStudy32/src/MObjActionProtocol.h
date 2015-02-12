#ifndef __MOBJACTIONPROTOCOL_H__
#define __MOBJACTIONPROTOCOL_H__
#include "glm/glm.hpp"

class MObjActionProtocol
{
public:	
	virtual ~MObjActionProtocol() {}
	virtual void initMatrix() = 0;
	virtual glm::mat4 getMVP() = 0;
protected:
	glm::mat4 projection;
	glm::mat4 View;
	glm::mat4 Model;	
};


#endif