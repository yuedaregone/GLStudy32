#ifndef __ClipSprite_H__
#define __ClipSprite_H__

class ClipSprite
{
private:
	ClipSprite() {}
	virtual ~ClipSprite() {}
public:
	static ClipSprite* createClipSprite(int _w, int _h);
	bool initClipSprite(int _w,int _h);
private:
	int m_width;
	int m_height;
};
#endif