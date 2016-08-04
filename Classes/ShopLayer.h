#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 

USING_NS_CC;
using namespace ui;

class ShopLayer : public cocos2d::Layer
{
public:
	ShopLayer();
	~ShopLayer();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ShopLayer);

private:
	bool initBackground();
	//bool initButtons();
	//bool initNotice();
};

