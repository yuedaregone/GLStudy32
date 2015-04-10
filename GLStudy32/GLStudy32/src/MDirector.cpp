#include "MDirector.h"
#include "GLDraw.h"
#include "Sprite.h"
#include "GLFilter.h"
#include "pic.h"
#include "png.h"
#include "GLSprite.h"

MDirector::MDirector()
	:m_isPause(false)
{
}

float temp = -1.2f;
float tmp = 0.0f;
Sprite* sp;
GLSprite* sp1;
GLDraw drawNode;
GLFilterUV* fliter;
void MDirector::init()
{
	//MGraphicsProtocol* glDraw = new MDrawTextureBox(); //gl draw class
	//glDraw->shaderInit();
	//glDraw->drawInit();

	//GLSprite* sp = GLSprite::createWithBMP("texture.bmp", 100, 100);
	//sp->setPosition(150, 150);
	//sp->setOpacity(0.3f);
	//sp->setScale(0.5f, 1.0f);
	//sp->setRotation(90);

	//sp1 = GLSprite::createWithBMP("texture.bmp", 50, -50);
	//sp1->setPosition(25, 25);
	//sp1->setScale(0.5f, 0.5f);
	//sp1->setColor(1.0f, 0.0f, 1.0f, 1.0f);

	//Sprite* sp = Sprite::createWithBMP("texture.bmp");//createWithDDS("texture.dds");
	sp = Sprite::createWithPNG("texture1.png");
	sp->setPosition(150, 150);

	//fliter = new GLFilterUV();
	//fliter->initFilter();
	//sp->setFilter(fliter);

	Sprite* sp0 = Sprite::createWithBMP("texture.bmp");
	sp0->setPosition(32, 268);
	sp0->setScale(0.5f);
	//sp0->setRotation(180.0f);

	GLFilterSpark* filter = new GLFilterSpark();
	filter->initFilter();
	filter->setSparkColor(1.0f, 0.0f, 1.0f, 1.0f);
	sp->setFilter(filter);
	//sp0->setFilter(filter);


	Sprite* sp1 = Sprite::createWithData(ImageData::imgPic_1, false, 128, 128);
	sp1->setScale(0.5f);
	sp1->setPosition(32, 32);
	//sp1->setFilter(filter);

	drawNode.initGLDraw();
	drawNode.setPointSize(2.0f);
	drawNode.setColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void MDirector::mainLoop()
{
	if (m_isPause)
	{
		return;
	}

	//glDraw->actionUpdate();
	//glDraw->drawUpdate(); //gl draw update
	sp->draw();
	//sp1->draw();

	//fliter->setUVOffset(tmp);
	if (tmp > 1.0f)
	{
		tmp = 0.02f;
	}
	else
	{
		tmp = tmp + 0.02f;
	}
	//drawNode.drawPoint(100, 110);

	//filter->setSparkOffset(temp);		
	//sp->draw();
	//sp0->draw();
	//sp1->draw();
	/*if (temp > 1.2f)
	{
		temp = -1.2f;
	}
	else
	{
		temp = temp + 0.02f;
	}*/
}

void MDirector::destroy()
{
	//delete glDraw;
	//sp->release();
}
