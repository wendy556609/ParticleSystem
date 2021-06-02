#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CParticle.h"
#include <list>

using namespace std;

class CParticleSystem
{
private:
	CParticle* _Particle;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;

	int _iInUsed;
	int _iFree;
	
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

	cocos2d::Color3B _color;
	std::string _SpriteName;

	int _iType;

	cocos2d::Point _emitterPos;
	bool _bEmitterOn;
public:
	float _fTime;
	int _iTotEmitterNum;
	int _iCurEmitterNum;

	CParticleSystem();
	~CParticleSystem();

	void init(cocos2d::Scene& stage);
	void update(float dt);

	void setType(int type);
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
	void setEmitterPos(cocos2d::Point pos);

	void setSprite(std::string &spriteName);

	void onEmitter(bool enable);
	void onTouchBegan(cocos2d::Point touchLoc); 
	void onTouchMoved(cocos2d::Point touchLoc);
	void onTouchEnded(cocos2d::Point touchLoc);
};