#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"

using namespace std;

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))
#define GRAVITY_Y(t,dt,g) ((g)*((t)+0.5f*(dt)))
#define LIFE_NOISE(f) ((f)*(1.0f-(rand()%2001/1000.0f)))

#define TOUCHPOINT 0
#define FALLPOINT 1
#define RANDOMPOINT 2
#define EXPLOSION 3
#define HEARTSTYLE 4
#define BUTTERFLYSTYLE 5

#define FIREWORKSTYLE 6
#define FIREWORKPOP 7
#define FIRE 8
#define SMOKE 9
#define LUCKY 10
#define CLEAR 11
#define RAIN 12
#define WAVE 13
#define SNOW 14
#define SNOWDROP 15
#define LOVE 16
#define EMITTER 99

class CParticle
{
private:
	cocos2d::Sprite* _Particle;
	cocos2d::Point _Pos;
	cocos2d::Point _Dir;

	float _fLifeTime;
	float _fTime;
	float _DelayTime;

	float _fGravity;
	float _fSpread;
	float _Spin;
	float _fOpacity;
	float _fSpeed;
	float _fSize;
	float _fScale;
	float _fDirAngle;

	cocos2d::Point _windDir;
	float _fWindForce;

	cocos2d::Color3B _color;
	std::string _SpriteName;

	bool _bVisible;
	bool _bChange;

	float _fModeTime;

	int _iType;
public:
	cocos2d::Point _range;
	cocos2d::Point _BornPos;

	CParticle();

	void setProperty(std::string pngname, cocos2d::Scene& stage);
	bool update(float dt);
	void setBehavior(int type);

	void setPosition(cocos2d::Point pos);
	void setVisible(bool visible);

	void setDirAngle(float DirAngle);
	void setScale(float Size);
	void setGravity(float Gravity);
	void setSpread(float Spread);
	void setDirection(cocos2d::Point Direction);
	void setSpin(float Spin);
	void setOpacity(float Opacity);
	void setSpeed(float Speed);
	void setLifetime(float Lifetime);
	void setColor(cocos2d::Color3B color);

	void setWindDir(cocos2d::Point WindDir);
	void setWindForce(float WindForce);

	void setSprite(std::string& spriteName);
};