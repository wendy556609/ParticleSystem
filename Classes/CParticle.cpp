#include "CParticle.h"

USING_NS_CC;

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))
#define GRAVITY_Y(t,dt,g) ((g)*((t)+0.5f*(dt)))
#define LIFE_NOISE(f) ((f)*(1.0f-(rand()%2001/1000.0f)))

inline int INTENSITY(float f) {
	if (f >= 255) return(255);
	else if (f <= 0) return(0);
	else return((int)f);
}

CParticle::CParticle() {
	_Particle = nullptr;
}

void CParticle::setProperty(std::string pngname, cocos2d::Scene& stage) {
	_Particle = Sprite::createWithSpriteFrameName(pngname);
	_Particle->setPosition(Point(0, 0));
	_color = Color3B(255, 255, 255);
	setVisible(false);

	BlendFunc blendfunc = { GL_SRC_ALPHA, GL_ONE };
	_Particle->setBlendFunc(blendfunc);

	stage.addChild(_Particle, 1);
}

bool CParticle::update(float dt) {
	float sint, cost , sin2t;
	if (!_bVisible && _fTime == 0) {
		setVisible(true);
		_Particle->setPosition(_Pos);
		_Particle->setColor(_color);
		
	}
	else if (_fTime > _fLifeTime) {
		setVisible(false);
		return true;
	}
	else {
		float dy, angle;
		switch (_iType)
		{
		case TOUCHPOINT:
		case FALLPOINT:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint * 2;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.y += (_Dir.y * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case RANDOMPOINT:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint * 2;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case EXPLOSION:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case HEARTSTYLE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case BUTTERFLYSTYLE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			sin2t = 3 * sinf(2.0f * M_PI * (_fTime * 2.0f / _fLifeTime));
			_fSize = 0.5f + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * sin2t * _fSpeed) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case EMITTER:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 0.5f + sint;
			_Particle->setScale(_fSize);
			angle = _fTime * _Spin;
			_Particle->setRotation(angle);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		default:
			break;
		}
		
	}
	_fTime += dt;
	return false;
}

void CParticle::setBehavior(int type) {
	float t;
	switch (type)
	{
	case TOUCHPOINT:
		_fTime = 0;
		_fLifeTime = 2.5f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
		_fSize = 1;
		_Dir.x = 0;
		_Dir.y = 0;
		_iType = TOUCHPOINT;
		break;
	case FALLPOINT:
		_fTime = 0;
		_fLifeTime = 2.5f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
		_fSize = 1;
		_Dir.x = 0;
		_Dir.y = -1;
		_iType = FALLPOINT;
		break;
	case RANDOMPOINT:
		_fTime = 0;
		_fLifeTime = 2.0f + LIFE_NOISE(0.2f);
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
		_fSize = 1;
		_fSpeed = _fSpeed + (rand() % 100 / 100.0f);
		t = 2.0f * M_PI * (rand() % 100 / 100.0f);
		_Dir.x = sinf(t);
		_Dir.y = cosf(t);
		_iType = RANDOMPOINT;
		break;
	case EXPLOSION:
		_fTime = 0;
		_fLifeTime = 2.0f + LIFE_NOISE(0.2f);
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
		_fSize = 1;
		_fSpeed = _fSpeed + (rand() % 100 / 100.0f);
		t = 2.0f * M_PI * (rand() % 100 / 100.0f);
		_Dir.x = sinf(t);
		_Dir.y = cosf(t);
		_iType = EXPLOSION;
		break;
	case HEARTSTYLE:
		_fTime = 0;
		_fLifeTime = 1.0f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 0 + rand() % 128, 0 + rand() % 128);
		_fSize = 1;
		t = 2.0f * M_PI * (rand() % 100 / 100.0f);
		float sint, cost, cos2t, cos3t, cos4t;
		sint = sinf(t); cost = cosf(t);
		cos2t = cosf(2 * t); cos3t = cosf(3 * t); cos4t = cosf(4 * t);
		_Dir.x = 16 * sint * sint * sint;
		_Dir.y = 13 * cost - 5 * cos2t - 2 * cos3t - cos4t;
		_iType = HEARTSTYLE;
		break;
	case BUTTERFLYSTYLE:
		_fTime = 0;
		_fLifeTime = 5.0f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 0 + rand() % 128, 0 + rand() % 128);
		_fSize = 1;
		t = 2.0f * M_PI * (rand() % 100 / 100.0f);
		float sin12t, sin512t, e;
		sint = sinf(t); cost = cosf(t);
		cos4t = cosf(4 * t); sin12t = sinf(t / 12.0f); sin512t = powf(sin12t, 5); e = expf(cost);
		_Dir.x = sint * (e - 2 * cos4t - sin512t);
		_Dir.y = cost * (e - 2 * cos4t - sin512t);
		_iType = BUTTERFLYSTYLE;
		break;
	case EMITTER:
		_fTime = 0;
		_fLifeTime = _fLifeTime + LIFE_NOISE(0.15f);
		_color = Color3B(INTENSITY(_color.r + rand() % 64), INTENSITY(_color.g + rand() % 64), INTENSITY(_color.b + rand() % 64));
		_fSize = 1;
		//_Particle->setSpriteFrame(_SpriteName);
		_iType = EMITTER;
		break;
	default:
		break;
	}
}

void CParticle::setPosition(cocos2d::Point pos) {
	_Pos = pos;
}

void CParticle::setVisible(bool visible) {
	_bVisible = visible;
	_Particle->setVisible(visible);
}

void CParticle::setGravity(float Gravity) {
	_fGravity = Gravity;
}

void CParticle::setSpread(float Spread) {
	_fSpread = Spread;
}

void CParticle::setDirection(cocos2d::Point Direction) {
	_Dir = Direction;
}

void CParticle::setSpin(float Spin) {
	_Spin = Spin;
}

void CParticle::setOpacity(float Opacity) {
	_fOpacity = Opacity;
}

void CParticle::setSpeed(float Speed) {
	_fSpeed = Speed;
}

void CParticle::setLifetime(float Lifetime) {
	_fLifeTime = Lifetime;
}

void CParticle::setColor(cocos2d::Color3B color) {
	_color = color;
}

void CParticle::setSprite(std::string& spriteName) {
	_SpriteName = spriteName;
	_Particle->setSpriteFrame(_SpriteName);
}