#ifndef __MGRAPHICSPROTOCOL_H__
#define __MGRAPHICSPROTOCOL_H__

class MGraphicsProtocol
{
public:
	virtual ~MGraphicsProtocol() {}
	virtual void shaderInit() = 0;	
	virtual void drawInit() = 0;
	virtual void actionUpdate() {}
	virtual void drawUpdate() = 0;
};

#endif