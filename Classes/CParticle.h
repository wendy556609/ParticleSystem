#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"

#define TOUCHPOINT 0
#define FALLPOINT 1
#define RANDOMPOINT 2
#define EXPLOSION 3
#define HEARTSTYLE 4
#define BUTTERFLYSTYLE 5

#define EMITTER 99

class CParticle
{
private:
	cocos2d::Sprite* _Particle;
	cocos2d::Point _Pos;
	cocos2d::Point _Dir;

	float _fLifeTime;
	float _fTime;

	float _fGravity;
	float _fSpread;
	float _Spin;
	float _fOpacity;
	float _fSpeed;
	float _fSize;

	cocos2d::Color3B _color;
	std::string _SpriteName;

	bool _bVisible;

	int _iType;
public:
	CParticle();

	void setProperty(std::string pngname, cocos2d::Scene& stage);
	bool update(float dt);
	void setBehavior(int type);

	void setPosition(cocos2d::Point pos);
	void setVisible(bool visible);

	void setGravity(float Gravity);
	void setSpread(float Spread);
	void setDirection(cocos2d::Point Direction);
	void setSpin(float Spin);
	void setOpacity(float Opacity);
	void setSpeed(float Speed);
	void setLifetime(float Lifetime);
	void setColor(cocos2d::Color3B color);
	void setSprite(std::string& spriteName);
};