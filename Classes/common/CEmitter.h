#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio �������
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
	bool onTouchMoved(const cocos2d::Point& touchLoc); //Ĳ�I���ʨƥ�
	bool onTouchEnded(const cocos2d::Point& touchLoc); //Ĳ�I�����ƥ� 

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