#include "ClipSprite.h"
#include <stdio.h>

ClipSprite* ClipSprite::createClipSprite(int _w, int _h)
{
	ClipSprite* pRet = new ClipSprite();
	if (pRet && pRet->initClipSprite(_w, _h))
	{
		return pRet;
	}
	delete pRet;
	return NULL;
}

bool ClipSprite::initClipSprite(int _w, int _h)
{
	return false;
}
