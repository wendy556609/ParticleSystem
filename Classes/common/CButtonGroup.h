#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CButton.h"

using namespace std;

enum Style {
	FLARE,
	BUBBLE
};

#define EMITTERBTN 0
#define STYLEBTN 1

class CButtonGroup
{
public:
	CButtonGroup();
	~CButtonGroup();

	static CButtonGroup* getInstance();
	static void Destroy();

	void init(cocos2d::Node &root, cocos2d::Scene& stage);
	bool getBtnState(int type);
	std::string getBtnSprite();

	bool onTouchBegan(const cocos2d::Point& touchLoc);
	bool onTouchMoved(const cocos2d::Point& touchLoc); //觸碰移動事件
	bool onTouchEnded(const cocos2d::Point& touchLoc); //觸碰結束事件 
private:
	cocos2d::Node* _uiRoot;
	CButton* _EmitterBtn;

	CButton* _curStyleBtn;
	CButton* _FlareBtn;
	CButton* _BubbleBtn;

	Style _style;
	bool _click;
};