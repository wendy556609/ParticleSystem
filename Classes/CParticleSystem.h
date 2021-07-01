#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CParticle.h"
#include "common/CEmitter.h"
#include <list>

class CParticleSystem
{
private:
	CParticle* _Particle;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;

	int _iInUsed;
	int _iFree;
	
	//Particle Value
	float _Gravity;
	float _Spread;
	float _Direction;
	float _Spin;
	float _Opacity;
	float _Number;
	float _Speed;
	float _Lifetime;
	float _Red;
	float _Green;
	float _Blue;

	float _WindForce;
	float _WindAngle;
	cocos2d::Point _WindDir;
	cocos2d::Point _Dir;
	float _DirAngle;

	cocos2d::Color3B _color;
	std::string _SpriteName;

	int _iType;
	int _iMode;

	cocos2d::Point _emitterPos;
	bool _bEmitterOn;

	//Mode
	bool _bfireworkTail;
	bool _bfireworkPop;
	bool _bluckyDraw;
	bool _bluckyClear;

	cocos2d::Point _MoveLoc;
	float _fModeSpeed;
public:
	float _fTheta;
	float _fModeTime;
	float _fTime;
	float _fBornTime;
	int _iTotEmitterNum;
	int _iCurEmitterNum;
	bool _bModeEnd;

	CParticleSystem();
	~CParticleSystem();

	void init(cocos2d::Scene& stage);
	void update(float dt);

	void setType(int type);
	void setMode(int Mode);
	void setGravity(float Gravity);
	void setSpread(float Spread);
	void setDirection(float Direction);
	void setSpin(float Spin);
	void setOpacity(float Opacity);
	void setNumber(int Number);
	void setSpeed(float Speed);
	void setLifetime(float Lifetime);
	void setRed(float Red);
	void setGreen(float Green);
	void setBlue(float Blue);
	void setWindDir(float WindDir);
	void setWindForce(float WindForce);
	void setEmitterPos(cocos2d::Point pos);

	void setSprite(std::string &spriteName);

	void onEmitter(bool enable);
	void onTouchBegan(cocos2d::Point touchLoc); 
	void onTouchMoved(cocos2d::Point touchLoc);
	void onTouchEnded(cocos2d::Point touchLoc);
};