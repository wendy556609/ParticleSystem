#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"

class CEmitter
{
public:
	CEmitter();
	~CEmitter();

	void setSprite(const std::string& pngname, cocos2d::Point pos, cocos2d::Scene& stage);
	void setPosition(cocos2d::Point pos);
	void setEnable(bool enable);
	void setInit();

	bool onTouchBegan(const cocos2d::Point& touchLoc);
	bool onTouchMoved(const cocos2d::Point& touchLoc); //觸碰移動事件
	bool onTouchEnded(const cocos2d::Point& touchLoc); //觸碰結束事件 

	cocos2d::Point getPosition();
private:
	cocos2d::Sprite* _Emitter;

	cocos2d::Point _initPos;
	cocos2d::Point _preLoc;
	cocos2d::Point _curLoc;

	cocos2d::Point _pos;
	cocos2d::Size _size;
	cocos2d::Rect _rect;

	bool _bEmitterOn;
	bool _bEnable;
	bool _isTouch;
};