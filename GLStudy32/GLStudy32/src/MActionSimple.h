#ifndef __MACTIONSIMPLE_H_
#define __MACTIONSIMPLE_H_
#include "MObjActionProtocol.h"

class MActionSimple : public MObjActionProtocol
{
public:
	virtual void initMatrix();
	virtual glm::mat4 getMVP();
};

#endif