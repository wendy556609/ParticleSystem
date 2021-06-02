#include "CParticleSystem.h"

USING_NS_CC;

#define NUM_PARTICLES 1000

CParticleSystem::CParticleSystem() {
	_Particle = nullptr;
}

CParticleSystem::~CParticleSystem() {
	if (_iInUsed != 0) _InUsedList.clear(); // 移除所有的 NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _Particle; // 釋放所有取得資源
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::init(cocos2d::Scene& stage) {
	_iFree = NUM_PARTICLES;
	_iInUsed = 0;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	_Particle = new CParticle[NUM_PARTICLES];

	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		_Particle[i].setProperty("flare.png", stage);
		_FreeList.push_front(&_Particle[i]);
	}

}

void CParticleSystem::update(float dt) {
	CParticle* get;
	list <CParticle*>::iterator it;
	if (_bEmitterOn) {
		int n = (int)(_fTime * _iTotEmitterNum);
		if (n > _iCurEmitterNum) {
			for (int i = 0; i < n - _iCurEmitterNum; i++)
			{
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setPosition(_emitterPos);
					get->setGravity(_Gravity);
					get->setSpin(_Spin);
					get->setOpacity(_Opacity);
					get->setSpeed(_Speed);
					get->setLifetime(_Lifetime);
					get->setColor(_color);
					get->setSprite(_SpriteName);
					float t = rand() % 101 / 100.0f;
					t = _Spread - t * _Spread * 2;
					t = (t + _Direction) * M_PI / 180.0f;
					Vec2 dir = Vec2(cosf(t), sinf(t));
					get->setDirection(dir);
					get->setBehavior(EMITTER);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--;
					_iInUsed++;
				}
			}
			_iCurEmitterNum = n;
		}
		if (_fTime >= 1.0f) {
			_fTime -= 1.0f;
			if (_iCurEmitterNum >= _iTotEmitterNum)_iCurEmitterNum -= _iTotEmitterNum;
			else _iCurEmitterNum = 0;
		}
		_fTime += dt;
	}
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end();)
		{
			if ((*it)->update(dt)) {
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it);
				_iFree++;
				_iInUsed--;
			}
			else it++;
		}
	}
}

void CParticleSystem::setEmitterPos(cocos2d::Point pos) {
	_emitterPos = pos;
}

void CParticleSystem::setType(int type) {
	_iType = type;
}

void CParticleSystem::setGravity(float Gravity) {
	_Gravity = Gravity;
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++)
		{
			(*it)->setGravity(_Gravity);
		}
	}
}

void CParticleSystem::setSpread(float Spread) {
	_Spread = Spread;
}

void CParticleSystem::setDirection(float Direction) {
	_Direction = Direction;
}

void CParticleSystem::setSpin(float Spin) {
	_Spin = Spin;
}

void CParticleSystem::setOpacity(float Opacity) {
	_Opacity = Opacity;
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++)
		{
			(*it)->setOpacity(_Opacity);
		}
	}
}

void CParticleSystem::setNumber(int Number) {
	_Number = Number;
	_iTotEmitterNum = _Number;
}

void CParticleSystem::setSpeed(float Speed) {
	_Speed = Speed;
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++)
		{
			(*it)->setSpeed(_Speed);
		}
	}
}

void CParticleSystem::setLifetime(float Lifetime) {
	_Lifetime = Lifetime;
}

void CParticleSystem::setRed(float Red) {
	_Red = Red;
	_color = Color3B(_Red, _Green, _Blue);
}

void CParticleSystem::setGreen(float Green) {
	_Green = Green;
	_color = Color3B(_Red, _Green, _Blue);
}

void CParticleSystem::setBlue(float Blue) {
	_Blue = Blue;
	_color = Color3B(_Red, _Green, _Blue);
}

void CParticleSystem::onEmitter(bool enable) {
	_bEmitterOn = enable;
}

void CParticleSystem::setSprite(std::string& spriteName) {
	_SpriteName = spriteName;
}

void CParticleSystem::onTouchBegan(cocos2d::Point touchLoc) {
	CParticle* get;
	switch (_iType)
	{
	case TOUCHPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(TOUCHPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case FALLPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(FALLPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case RANDOMPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(RANDOMPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case EXPLOSION:
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++)
			{
				get = _FreeList.front();
				get->setPosition(touchLoc);
				get->setGravity(_Gravity);
				get->setOpacity(_Opacity);
				get->setSpeed(_Speed);
				get->setSprite(_SpriteName);
				get->setBehavior(EXPLOSION);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--;
				_iInUsed++;
			}
		}
		else return;
		break;
	case HEARTSTYLE:
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++)
			{
				get = _FreeList.front();
				get->setPosition(touchLoc);
				get->setGravity(_Gravity);
				get->setOpacity(_Opacity);
				get->setSpeed(_Speed);
				get->setSprite(_SpriteName);
				get->setBehavior(HEARTSTYLE);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--;
				_iInUsed++;
			}
		}
		break;
	case BUTTERFLYSTYLE:
		if (_iFree > 200) {
			for (int i = 0; i < 200; i++)
			{
				get = _FreeList.front();
				get->setPosition(touchLoc);
				get->setGravity(_Gravity);
				get->setOpacity(_Opacity);
				get->setSpeed(_Speed);
				get->setSprite(_SpriteName);
				get->setBehavior(BUTTERFLYSTYLE);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--;
				_iInUsed++;
			}
		}
		break;
	default:
		break;
	}
	
}

void CParticleSystem::onTouchMoved(cocos2d::Point touchLoc) {
	CParticle* get;
	switch (_iType)
	{
	case TOUCHPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(TOUCHPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case FALLPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(FALLPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case RANDOMPOINT:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setPosition(touchLoc);
			get->setGravity(_Gravity);
			get->setOpacity(_Opacity);
			get->setSpeed(_Speed);
			get->setSprite(_SpriteName);
			get->setBehavior(RANDOMPOINT);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--;
			_iInUsed++;
		}
		else return;
		break;
	case EXPLOSION:
	case HEARTSTYLE:
	case BUTTERFLYSTYLE:
		break;
	default:
		break;
	}
}

void CParticleSystem::onTouchEnded(cocos2d::Point touchLoc) {

}