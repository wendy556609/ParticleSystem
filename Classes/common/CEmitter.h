#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"
#include "CParticle.h"

using namespace std;

#define POINT 0
#define LINE 1
#define PLANE 2

class CEmitter
{
public:
	CEmitter();
	~CEmitter();

	static CEmitter* getInstance();
	static void Destroy();

	void setSprite(const std::string& pngname, cocos2d::Point pos, cocos2d::Scene& stage);
	void setPosition(cocos2d::Point pos);
	void setEnable(bool enable);
	void setType(int type);
	void setInit();

	bool update(float dt);

	bool onTouchBegan(const cocos2d::Point& touchLoc);
	bool onTouchMoved(const cocos2d::Point& touchLoc); //觸碰移動事件
	bool onTouchEnded(const cocos2d::Point& touchLoc); //觸碰結束事件 

	cocos2d::Point getPosition();

	cocos2d::Sprite* _BornEmitter;
private:
	cocos2d::Sprite* _Emitter;
	cocos2d::Sprite* _Change; //rectEmitter

	cocos2d::Point _Dir;
	cocos2d::Point _initPos;
	cocos2d::Point _preLoc;
	cocos2d::Point _curLoc;
	cocos2d::Point _LoveInit[4];

	cocos2d::Size _planeSize;

	cocos2d::Point _pos;
	cocos2d::Size _size;
	cocos2d::Rect _rect;

	cocos2d::Point _changePos;
	cocos2d::Size _changeSize;
	cocos2d::Rect _changeRect;

	bool _bEmitterOn;
	bool _bEnable;
	bool _isTouch;
	bool _isAuto;
	bool _isChange;

	bool _isChangeTouch;

	int _iType;

	int _iLove;

	float _fTime;
	float _fModeTime;
};