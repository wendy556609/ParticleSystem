#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CButton.h"
#include "CParticle.h"

enum Style {
	FLARE,
	BUBBLE,
	COMET,
	Circle,
	Cloud,
	Spark
};

#define EMITTERBTN 0
#define STYLEBTN 1
#define MODEBTN 2

class CButtonGroup
{
public:
	CButtonGroup();
	~CButtonGroup();

	static CButtonGroup* getInstance();
	static void Destroy();

	void init(cocos2d::Node &root, cocos2d::Scene& stage);
	void setModeVisible(bool visible);
	void setSpriteVisible(bool visible);
	bool getBtnState(int type);
	std::string getBtnSprite();
	int getBtnMode();

	bool onTouchBegan(const cocos2d::Point& touchLoc);
	bool onTouchMoved(const cocos2d::Point& touchLoc); //觸碰移動事件
	bool onTouchEnded(const cocos2d::Point& touchLoc); //觸碰結束事件 
private:
	cocos2d::Node* _uiRoot;
	CButton* _EmitterBtn;

	//listBtn
	CButton* _OpenSpriteBtn;
	CButton* _CloseSpriteBtn;
	CButton* _OpenModeBtn;
	CButton* _CloseModeBtn;

	//Particle Style
	CButton* _curStyleBtn;
	CButton* _FlareBtn;
	CButton* _BubbleBtn;
	CButton* _CometBtn;
	CButton* _CircleBtn;
	CButton* _CloudBtn;
	CButton* _SparkBtn;

	//Particle Mode
	CButton* _curModeBtn;
	CButton* _FireworkBtn;
	CButton* _FireBtn;
	CButton* _LuckyBtn;
	CButton* _RainBtn;
	CButton* _SnowBtn;
	CButton* _LoveBtn;

	Style _style;
	int _Mode;
};