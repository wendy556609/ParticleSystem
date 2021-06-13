#include "CParticle.h"

USING_NS_CC;

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
	float cos2t;
	Point windDir;
	Point dir;
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
			_Pos.x += (_Dir.x * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
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
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
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
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
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
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
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
			_Pos.x += (_Dir.x * sin2t * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case STARSTYLE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case FLOWERSTYLE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case EMITTER:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 0.5f + sint;
			_Particle->setScale(_fSize);
			angle = (90.0f - _fDirAngle) + _fTime * _Spin;
			_Particle->setRotation(angle);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) *dt* PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case FIREWORKSTYLE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1.0f * _fScale;
			_Particle->setScale(_fSize);
			angle = 90.0f - _fDirAngle;
			_Particle->setRotation(angle);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost * _fSpeed ) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case FIREWORKPOP:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1.0f * _fScale;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			angle = 90.0f - _fDirAngle;
			_Particle->setRotation(angle);
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cost *_fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case FIRE:
			if (_fTime > _fModeTime) {
				if (!_bChange) {
					_bChange = true;
					std::string smoke = "cloud.png";
					setSprite(smoke);
					_color = Color3B::GRAY;
					_fTime = 0;
					_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
					_fOpacity = 128;
					_Dir = Point(0, 1);
					_iType = SMOKE;
				}
			}
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			sin2t = 2.0f * sinf(M_PI * (_fTime / _fLifeTime));
			cos2t = cosf(M_PI * (_fTime / _fLifeTime));
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));

			windDir = _windDir;
			if (windDir.y < 0) {
				windDir.y = 0;
			}
			
			_Pos.x += (_Dir.x * cos2t * _fSpeed + (windDir.x * (_fWindForce * 0.25f) * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * sin2t * _fSpeed + (windDir.y * (_fWindForce * 0.25f) * sint)) * dt * PIXEL_PERM;

			_Particle->setPosition(_Pos);
			break;
		case SMOKE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1.0f + cost;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);

			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;

			_Particle->setPosition(_Pos);
			break;
		case LUCKY:
			if (_fTime > _fModeTime) {
				if (!_bChange) {
					_bChange = true;
					_fTime = 0;
					_fLifeTime = 5.0f + LIFE_NOISE(0.15f);
					if (_Pos.x > _range.x) {
						if (_Pos.y > _range.y)
							_Dir = Point(1, 1);
						else
							_Dir = Point(1, -1);
					}
					else {
						if (_Pos.y > _range.y)
							_Dir = Point(-1, 1);
						else
							_Dir = Point(-1, -1);
					}
					_fSpeed = 1.0f;
					_iType = CLEAR;
				}
			}
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1.0f + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);

			//_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			//_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;

			_Particle->setPosition(_Pos);
			break;
		case CLEAR:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1.0f + cost;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);

			_Pos.x += (_Dir.x * cost * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;

			_Particle->setPosition(_Pos);
			break;
		case RAIN:
			if (_fTime > _fModeTime) {
				if (!_bChange) {
					_bChange = true;
					_fTime = 0;
					std::string sprite = "ripple.png";
					setSprite(sprite);
					_color = Color3B::GRAY;
					_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
					_iType = WAVE;
				}
			}
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));

			if (_fDirAngle > 180.0f && _fDirAngle <= 360.0f) {
				_fDirAngle = 360.0f - _fDirAngle;
			}

			angle = _fDirAngle - 270.0f;
			if (angle < -225.0f)
				angle = -225.0f;
			else if (angle > -135.0f)
				angle = -135.0f;

			if (_fWindForce == 0)
				angle = 0;

			if (_windDir.y > 0) {
				_windDir.y = -1;
			}

			_Particle->setRotation(angle);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));

			_Pos.x += (_Dir.x * _fSpeed + (_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * _fSpeed + (_windDir.y * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case WAVE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_fSize = 1 + sint;
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setRotation(0);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			
			_Particle->setPosition(_Pos);
			break;
		case SNOW:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			sin2t = sinf(M_PI_2 * (_fTime / _fLifeTime));
			float size;
			size = _fSize * 1.0f * sin2t;
			_Particle->setScale(size);
			_Particle->setScale(_fSize);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += ((_windDir.x * _fWindForce * sint)) * dt * PIXEL_PERM;
			_Pos.y += ((_windDir.y * _fWindForce * sint) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);

			if (_fTime > _fModeTime) {
				if (!_bChange) {
					_bChange = true;
					float noise, t;
					noise = LIFE_NOISE(0.2f);
					_fTime = 0;
					_fLifeTime = 4.0f + noise;
					_color = Color3B::GRAY;
					_fSpeed = 3.0f + noise;
					_Spin = -90 + random() % 180;
					t = 2.0f * M_PI * (rand() % 100 / 100.0f);
					_Dir.x = sinf(t);
					_Dir.y = -1;
					_iType = SNOWDROP;
				}
			}
			break;
		case SNOWDROP:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			cos2t = cosf(M_PI * (_fTime * 2 / _fLifeTime));
			size = _fSize * 1.0f * cost;
			angle = _fTime * _Spin;
			_Particle->setRotation(angle);
			_Particle->setScale(size);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			dy = GRAVITY_Y(_fTime, dt, _fGravity);
			_Pos.x += (_Dir.x * cos2t * _fSpeed + (_windDir.x * _fWindForce * sint * 3.0f)) * dt * PIXEL_PERM;
			_Pos.y += (_Dir.y * cost * _fSpeed + (_windDir.y * _fWindForce * sint * 3.0f) + dy) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			break;
		case LOVE:
			sint = sinf(M_PI * (_fTime / _fLifeTime));
			cost = cosf(M_PI_2 * (_fTime / _fLifeTime));
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (0.5f + sint)), INTENSITY(_color.g * (0.5f + sint)), INTENSITY(_color.b * (0.5f + sint))));
			
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
		_Dir.x = (16 * sint * sint * sint) * 0.1f;
		_Dir.y = (13 * cost - 5 * cos2t - 2 * cos3t - cos4t) * 0.1f;
		//_Dir.x = 16 * sint * sint * sint;
		//_Dir.y = 13 * cost - 5 * cos2t - 2 * cos3t - cos4t;
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
		_Dir.x = 0.25f * sint * (e - 2 * cos4t - sin512t);
		_Dir.y = 0.25f * cost * (e - 2 * cos4t - sin512t);
		_iType = BUTTERFLYSTYLE;
		break;
	case STARSTYLE:
		_fTime = 0;
		_fLifeTime = 1.0f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 0 + rand() % 128);
		_fSize = 1;
		t = 2.0f * M_PI * (rand() % 101 / 100.0f);
		float sin5t, r;
		sint = sinf(t); cost = cosf(t);
		sin5t = sinf(_fDirAngle - 5 * t);
		r = 5.0f - sin5t;
		_Dir.x = r * cost * 0.5f;
		_Dir.y = r * sint * 0.5f;
		_iType = STARSTYLE;
		break;
	case FLOWERSTYLE:
		_fTime = 0;
		_fLifeTime = 1.0f + LIFE_NOISE(0.15f);
		_color = Color3B(64 + rand() % 128, 0 + rand() % 128, 0 + rand() % 128);
		_fSize = 1;
		t = 2.0f * M_PI * (rand() % 101 / 100.0f);
		sint = sinf(t); cost = cosf(t);
		sin5t = sinf(_fDirAngle - 5 * t); 
		r = 1.0f - sin5t;
		_Dir.x = r * cost;
		_Dir.y = r * sint;
		_iType = FLOWERSTYLE;
		break;
	case EMITTER:
		_fTime = 0;
		_fLifeTime = _fLifeTime + LIFE_NOISE(0.15f);
		_color = Color3B(INTENSITY(_color.r + rand() % 64), INTENSITY(_color.g + rand() % 64), INTENSITY(_color.b + rand() % 64));
		_fSize = 1;
		//_Particle->setSpriteFrame(_SpriteName);
		_iType = EMITTER;
		break;
	case FIREWORKSTYLE:
		_fTime = 0;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_color = Color3B(INTENSITY(_color.r + rand() % 128), INTENSITY(_color.g + rand() % 128), INTENSITY(_color.b + rand() % 128));
		_fGravity = 0;
		_Particle->setRotation(_Spin);
		_fSpeed = 5.0f;
		//_Particle->setSpriteFrame(_SpriteName);
		_iType = FIREWORKSTYLE;
		break;
	case FIREWORKPOP:
		_fTime = 0;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_color = Color3B(INTENSITY(_color.r + rand() % 128), INTENSITY(_color.g + rand() % 128), INTENSITY(_color.b + rand() % 128));
		_fGravity = 0;
		_fSpeed = 8.0f + (rand() % 500 / 100.0f);
		_fSize = 1.0f * _fScale;
		_Particle->setScale(_fSize);
		_fGravity = -5.0f;
		//_fSize = 1;
		//_Particle->setSpriteFrame(_SpriteName);
		_iType = FIREWORKPOP;
		break;
	case FIRE:
		_fTime = 0;
		float noise;
		noise = LIFE_NOISE(0.15f);
		_fLifeTime = 3.0f + noise;
		_color = Color3B(INTENSITY(_color.r + rand() % 32), INTENSITY(0 + rand() % 32), INTENSITY(0 + rand() % 32));
		t = rand() % 200 / 100.0f;
		_fSize = 1 + t;
		_fSpeed = 2.0f + (rand() % 400 / 100.0f);
		_Particle->setRotation(0);
		_iType = FIRE;
		_fModeTime = 2.0f + noise;
		_bChange = false;
		break;
	case LUCKY:
		_fTime = 0;
		noise = LIFE_NOISE(0.15f);
		_fLifeTime = 10.0f + noise;
		_color = Color3B(INTENSITY(0 + rand() % 32), INTENSITY(_color.g + rand() % 32), INTENSITY(0 + rand() % 32));
		_fGravity = 0;
		_fSpeed = 1.0f;
		_fModeTime = 5.0f + noise;
		_bChange = false;
		_iType = LUCKY;
		break;
	case RAIN:
		_fTime = 0;
		noise = LIFE_NOISE(0.15f);
		_fLifeTime = 4.0f + noise;
		_color = Color3B(INTENSITY(_color.r + rand() % 128), INTENSITY(_color.g + rand() % 128), INTENSITY(_color.b + rand() % 128));
		_fGravity = 0;
		_Dir.x = 0;
		_Dir.y = -1;
		_fSpeed = 5.0f;
		_fSize = 1;
		_Particle->setScale(_fSize);
		_fModeTime = 3.0f + noise;
		_bChange = false;
		_iType = RAIN;
		break;
	case SNOW:
		_fTime = 0;
		noise = LIFE_NOISE(0.2f);
		_fLifeTime = 1.0f + noise;
		_color = Color3B::GRAY;
		t = rand() % 101 / 100.0f;
		_fSize = 0.25f + t;
		_Particle->setScale(_fSize);
		_Dir.x = 0;
		_Dir.y = 0;
		_fSpeed = 0;
		_fModeTime = 0.75f + noise;
		_bChange = false;
		_iType = SNOW;
		break;
	case LOVE:
		_fTime = 0;
		noise = LIFE_NOISE(0.2f);
		_fLifeTime = 10.0f + noise;
		_color = Color3B(INTENSITY(_color.r + rand() % 128), INTENSITY(0 + rand() % 128), INTENSITY(0 + rand() % 128));
		_fSize = 1;
		_Particle->setScale(_fSize);
		_iType = LOVE;
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

void CParticle::setDirAngle(float DirAngle) {
	_fDirAngle = DirAngle;
}

void CParticle::setScale(float Size) {
	_fScale = Size;
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

void CParticle::setWindDir(cocos2d::Point WindDir) {
	_windDir = WindDir;
}
void CParticle::setWindForce(float WindForce) {
	_fWindForce = WindForce;
}