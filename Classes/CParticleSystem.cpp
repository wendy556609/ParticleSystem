#include "CParticleSystem.h"

USING_NS_CC;

#define NUM_PARTICLES 1000

CParticleSystem::CParticleSystem() {
	_Particle = nullptr;

	_bfireworkTail = true;

	_bModeEnd = true;
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
	
		int n;
		if (_bEmitterOn) {
		switch (_iMode)
		{
		case EMITTER:
			
				_bModeEnd = false;
				n = (int)(_fTime * _iTotEmitterNum);
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
							_DirAngle = (t + _Direction);
							t = (t + _Direction) * M_PI / 180.0f;
							Vec2 dir = Vec2(cosf(t), sinf(t));
							get->setDirection(dir);
							get->setDirAngle(_DirAngle);
							get->setWindDir(_WindDir);
							get->setWindForce(_WindForce);
							get->setBehavior(EMITTER);
							_FreeList.pop_front();
							_InUsedList.push_front(get);
							_iFree--;
							_iInUsed++;
						}
					}
					_iCurEmitterNum = n;
				}
				_fTime += dt;
				if (_fTime >= 1.0f) {
					_bModeEnd = true;
					_fTime -= 1.0f;
					if (_iCurEmitterNum >= _iTotEmitterNum)_iCurEmitterNum -= _iTotEmitterNum;
					else _iCurEmitterNum = 0;
				}
			break;
		case FIREWORKSTYLE:
			if (_bfireworkTail) {
				if (_fTime == 0) {
					_bModeEnd = false;
					_MoveLoc = _emitterPos;

					_Direction = 90;
					float t = rand() % 101 / 100.0f;
					t = 45.0f - t * 45.0f * 2;
					_DirAngle = (t + _Direction);
					t = (t + _Direction) * M_PI / 180.0f;
					_Dir = Vec2(cosf(t), sinf(t));

					_fModeSpeed = rand() % 10 + 10.0f;
				}
				float sint = sinf(M_PI_2 * (_fTime / _fModeTime));

				_MoveLoc += _Dir * _fModeSpeed * dt * PIXEL_PERM;
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setPosition(_MoveLoc);
					get->setScale(sint);
					get->setSpin(_Spin);
					get->setDirAngle(_DirAngle);
					get->setOpacity(_Opacity);
					get->setLifetime(_Lifetime);
					get->setColor(_color);
					get->setSprite(_SpriteName);
					get->setDirection(_Dir);
					get->setBehavior(FIREWORKSTYLE);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--;
					_iInUsed++;
				}
				_fTime += dt;
				if (_fTime > _fModeTime) {
					_bfireworkTail = false;
					_bfireworkPop = true;
					_fTime = 0;
					_fModeTime = 1.0f;
				}
			}
			else if (_bfireworkPop) {
				float sint = cosf(M_PI * (_fTime / _fModeTime));
				float cost = cosf(M_PI_2 * (_fTime / _fModeTime));
				float t = rand() % 101 / 100.0f;
				t = 180.0f - t * 180.0f * 2;
				_DirAngle = (t + _Direction);
				t = (t + _Direction) * M_PI / 180.0f;
				Vec2 dir = Vec2(cosf(t), sinf(t));
				if (_iFree > 10) {
					for (int i = 0; i < 10; i++)
					{
						get = _FreeList.front();
						get->setPosition(_MoveLoc);
						get->setScale(cost);
						get->setGravity(_Gravity);
						get->setSpin(_Spin);
						get->setDirAngle(_DirAngle);
						get->setOpacity(_Opacity);
						get->setSpeed(_Speed);
						get->setLifetime(_Lifetime);
						get->setColor(_color);
						get->setSprite(_SpriteName);
						//float t = _Direction * M_PI / 180.0f;
						get->setDirection(dir);
						get->setWindDir(_WindDir);
						get->setWindForce(_WindForce);
						get->setBehavior(FIREWORKPOP);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--;
						_iInUsed++;
					}
				}
				_fTime += dt;
				if (_fTime > _fModeTime) {
					_bModeEnd = true;
					_bfireworkTail = true;
					_bfireworkPop = false;
					_fTime = 0;
					_fModeTime = 1.0f + (rand() % 200 / 100.0f);
				}
			}
			break;
		case FIRE:
			_bModeEnd = false;
			n = (int)(_fTime * _iTotEmitterNum);
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
						string sprite = "fire.png";
						get->setSprite(sprite);
						float t = rand() % 101 / 100.0f;
						t = 90.0f - t * 90.0f * 2;
						_Direction = 90;
						t = (t + _Direction) * M_PI / 180.0f;
						Vec2 dir = Vec2(cosf(t), sinf(t));
						get->setDirection(dir);
						get->setWindDir(_WindDir);
						get->setWindForce(_WindForce);
						get->setBehavior(FIRE);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--;
						_iInUsed++;
					}
				}
				_iCurEmitterNum = n;
			}
			_fTime += dt;
			if (_fTime >= 1.0f) {
				_bModeEnd = true;
				_fTime -= 1.0f;
				if (_iCurEmitterNum >= _iTotEmitterNum)_iCurEmitterNum -= _iTotEmitterNum;
				else _iCurEmitterNum = 0;
			}
			break;
		case Lucky:
			if (_fTime == 0) {
				_bModeEnd = false;
				_MoveLoc = _emitterPos;
				_DirAngle = 0;
			}
			float t, r;
			_DirAngle++;
			t = _DirAngle * M_PI / 180.0f;
			r = 5.0f * sinf(2 * t);
			_Dir = Vec2(r * cosf(t), r * sinf(t));
			_MoveLoc += _Dir * dt * PIXEL_PERM;
			if (_iFree != 0) {
				get = _FreeList.front();
				get->setPosition(_MoveLoc);
				get->setScale(1.0f);
				get->setSpin(_Spin);
				get->setOpacity(_Opacity);
				get->setLifetime(_Lifetime);
				get->setColor(_color);
				get->setSprite(_SpriteName);
				get->setDirection(_Dir);
				get->setBehavior(Lucky);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--;
				_iInUsed++;
			}
			_fTime += dt;
			break;
		default:
			break;
		}
		}
		else {
			_bModeEnd = true;
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

void CParticleSystem::setMode(int Mode) {
	_iMode = Mode;
	switch (_iMode)
	{
	case EMITTER:
		_fTime = 0;
		break;
	case FIREWORKSTYLE:
		_fTime = 0;
		_fModeTime = 1.5f;
		_bfireworkTail = true;
		_bfireworkPop = false;
		break;
	case FIRE:
		_fTime = 0;
		_fModeTime = 3.0f;
		_iTotEmitterNum = 100;
		break;
	case Lucky:
		_fTime = 0;
		_fModeTime = 10.0f;
		break;
	default:
		break;
	}
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

void CParticleSystem::setWindDir(float WindDir) {
	list <CParticle*>::iterator it;
	float t = WindDir * M_PI / 180.0f;
	cocos2d::Point dir = Vec2(cosf(t), sinf(t));
	_WindDir = dir;
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++)
		{
			(*it)->setWindDir(_WindDir);
		}
	}
}

void CParticleSystem::setWindForce(float WindForce) {
	_WindForce = WindForce;
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) {
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++)
		{
			(*it)->setWindForce(_WindForce);
		}
	}
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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
				get->setWindDir(_WindDir);
				get->setWindForce(_WindForce);
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
				get->setWindDir(_WindDir);
				get->setWindForce(_WindForce);
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
				get->setWindDir(_WindDir);
				get->setWindForce(_WindForce);
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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
			get->setWindDir(_WindDir);
			get->setWindForce(_WindForce);
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