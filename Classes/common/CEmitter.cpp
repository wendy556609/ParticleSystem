#include "CEmitter.h"

USING_NS_CC;

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))

CEmitter* _SEmitter;

CEmitter::CEmitter()
{
	_LoveInit[0] = Point(612.5f, 540); _LoveInit[1] = Point(857.5f, 440); _LoveInit[2] = Point(1102.5f, 440); _LoveInit[3] = Point(1377.5f, 540);
	_Emitter = nullptr;
	_Change = nullptr;

	_isChangeTouch = false;
	_isTouch = false;
	_bEnable = false;

	_isAuto = false;
	_isChange = false;
	_fTime = 0;
	_fModeTime = 0;
}

CEmitter::~CEmitter()
{
}

CEmitter* CEmitter::getInstance() {
	if (_SEmitter == nullptr)_SEmitter = new(nothrow)CEmitter();
	return _SEmitter;
}

void CEmitter::Destroy() {
	if (_SEmitter != nullptr)CC_SAFE_DELETE(_SEmitter);
}

void CEmitter::setSprite(const std::string& pngname, cocos2d::Point pos, cocos2d::Scene& stage) {
	_Emitter = Sprite::createWithSpriteFrameName(pngname);
	_Change = Sprite::createWithSpriteFrameName("emittericon1.png");

	_size = _Emitter->getContentSize();
	_initPos = pos;

	_changeSize = _Change->getContentSize();
	_planeSize = Size(1080, 800);

	setPosition(pos);

	_Emitter->setVisible(false);
	_Change->setVisible(false);

	stage.addChild(_Emitter, 10);
	stage.addChild(_Change, 11);
}

bool CEmitter::update(float dt) {
	if (_isAuto) {
		float t = 0;
		_fModeTime += dt;
		switch (_iLove)
		{
		case 0:
			if (!_isChange) {
				_isChange = true;
				_pos = _LoveInit[0] + Point(-50.0f, 100.0f);
				_Dir = Point(1, -1);
				_fTime = 0;
			}
			if (_pos.y >= (_LoveInit[0].y - 100.0f))
				_pos.y += _Dir.y * 10.0f * dt * PIXEL_PERM;
			else if (_pos.x <= (_LoveInit[0].x + 50.0f))
				_pos.x += _Dir.x * 10.0f * dt * PIXEL_PERM;
			else {
				_isChange = false;
				_iLove = 1;
			}
			break;
		case 1:
			if (!_isChange) {
				_isChange = true;
				_pos = _LoveInit[1];
				_fTime = 0;
			}
			t = 2.0f * M_PI * (_fTime / 2.0f);
			_Dir = Point(1 * cosf(t), 1 * sinf(t));
			_pos.x += _Dir.x * 10.0f * dt * PIXEL_PERM;
			_pos.y += _Dir.y * 10.0f * dt * PIXEL_PERM;
			if (_fTime >= 2.0f) {
				_isChange = false;
				_iLove = 2;
			}
			break;
		case 2:
			if (!_isChange) {
				_isChange = true;
				_pos = _LoveInit[2]+ Point(-100.0f, 0);
				_Dir = Point(-100.0f, 0);
				_fTime = 0;
			}
			if (_pos.x <= (_LoveInit[2].x + 100)) {
				_Dir.x += 10.0f * dt * PIXEL_PERM;
				_Dir.y = abs(-2 * _Dir.x);
				_pos.x = _LoveInit[2].x + _Dir.x;
				_pos.y = _LoveInit[2].y + _Dir.y;
			}
			else {
				_isChange = false;
				_iLove = 3;
			}
			break;
		case 3:
			if (!_isChange) {
				_isChange = true;
				_pos = _LoveInit[3];
				_Dir = Point(0, 100.0f);
				_fTime = 0;
			}
			
			if (_pos.y >= (_LoveInit[3].y - 90.0f)) {
				_Dir.y -= 20.0f * dt * PIXEL_PERM;
				t = _Dir.y / 30.0f;
				t = sinf(t);
				_Dir.x = -3 * abs(t) * 50.0f * dt * PIXEL_PERM;
				_pos.x = _LoveInit[3].x + _Dir.x;
				_pos.y = _LoveInit[3].y + _Dir.y;
			}
			else {
				_isChange = false;
				_iLove = 4;
			}
			break;
		case 4:
			if (_fModeTime >= 12.0f) {
				_isChange = false;
				_iLove = 0;
				_fModeTime = 0;
				_pos = _LoveInit[0] + Point(-50.0f, 100.0f);
			}
			return false;
			break;
		default:
			break;
		}
		
		setPosition(_pos);

		_fTime += dt;
		return true;
	}
	return false;
}

bool CEmitter::onTouchBegan(const cocos2d::Point& touchLoc) {
	if (_bEnable && !_isAuto) {
		if (_rect.containsPoint(touchLoc)) {
			_preLoc = touchLoc;
			_isTouch = true;
			return true;
		}
		else if (_changeRect.containsPoint(touchLoc)) {
			_preLoc = touchLoc;
			_isChangeTouch = true;
			return true;
		}
	}
	return false;
}

bool CEmitter::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (_bEnable && !_isAuto) {
		if (_isTouch) {
			Point dir, pos;
			switch (_iType)
			{
			case POINT:
				_curLoc = touchLoc;
				dir = _curLoc - _preLoc;
				pos = _pos + dir;
				setPosition(pos);
				_preLoc = _curLoc;
				break;
			case LINE:
				_curLoc = touchLoc;
				dir = _curLoc - _preLoc;
				pos = _pos + dir;
				setPosition(Point(_pos.x, pos.y));
				_preLoc = _curLoc;
				break;
			case PLANE:
				_curLoc = touchLoc;
				dir = _curLoc - _preLoc;
				pos = _pos + dir;
				setPosition(pos);
				_preLoc = _curLoc;
				break;
			default:
				break;
			}
			return true;
		}
		else if (_isChangeTouch) {
			Point dir, pos;
			_curLoc = touchLoc;
			dir = _curLoc - _preLoc;
			_size = Size((_size.width + dir.x), (_size.height + dir.y));
			_planeSize = _size;
			_Emitter->setContentSize(_planeSize);
			setPosition(_pos);
			_preLoc = _curLoc;
		}
	}
	
	return false;
}

bool CEmitter::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (_bEnable && !_isAuto) {
		if (_rect.containsPoint(touchLoc) && _isTouch) {
			_isTouch = false;
			return true;
		}
		else if (_changeRect.containsPoint(touchLoc) && _isChangeTouch) {
			_isChangeTouch = false;
			return true;
		}
	}
	return false;
}

void CEmitter::setPosition(cocos2d::Point pos) { 
	_pos = pos;
	_rect = Rect(_pos.x - _size.width / 2.0f, _pos.y - _size.height / 2.0f, _size.width, _size.height);
	_Emitter->setPosition(_pos);

	Point changePos = Point(_pos.x + _size.width / 2.0f, _pos.y + _size.height / 2.0f);
	_changePos = changePos;
	_changeRect = Rect(_changePos.x - _changeSize.width / 2.0f, _changePos.y - _changeSize.height / 2.0f, _changeSize.width, _changeSize.height);
	_Change->setPosition(_changePos);
}

void CEmitter::setEnable(bool enable) {
	_bEnable = enable;
	_Emitter->setVisible(enable);
	_Change->setVisible(false);
}

void CEmitter::setInit() {
	setPosition(_initPos);
}

void CEmitter::setType(int type) {
	if (type == LOVE) {
		if (!_isAuto) {
			_isAuto = true;
			_isChangeTouch = false;
			_pos = _LoveInit[0] + Point(-50.0f, 100.0f);
			_iLove = 0;
		}
	}
	else {
		if (_isAuto)
			_isAuto = false;
	}
	switch (type)
	{
	case FIREWORKSTYLE:
	case RAIN:
		_pos.x = _initPos.x;
		_Emitter->setSpriteFrame("sliderProgress.png");
		_size = Size(1920, 10);
		_Emitter->setContentSize(_size);
		setPosition(_pos);
		_iType = LINE;
		break;
	case SNOW:
		_Emitter->setSpriteFrame("rectEmitter.png");
		_size = _planeSize;
		_Emitter->setContentSize(_planeSize);
		setPosition(_pos);
		_Change->setVisible(true);
		_iType = PLANE;
		break;
	default:
		_Emitter->setSpriteFrame("emittericon.png");
		_size = Size(74, 74);
		_Emitter->setContentSize(_size);
		setPosition(_pos);
		_iType = POINT;
		break;
	}
}


cocos2d::Point CEmitter::getPosition() {
	Point pos;
	switch (_iType)
	{
	case POINT:
		return _pos;
		break;
	case LINE:
		pos.x = (-800.0f + random() % 1600) + _pos.x;
		pos.y = (-5.0f + random() % 10) + _pos.y;
		return pos;
		break;
	case PLANE:
		pos.x = (-(_planeSize.width / 2) + random() % (int)_planeSize.width) + _pos.x;
		pos.y = (-(_planeSize.height / 2) + random() % (int)_planeSize.height) + _pos.y;
		return pos;
		break;
	default:
		break;
	}
	return _pos;
}