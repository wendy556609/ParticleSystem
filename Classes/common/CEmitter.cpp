#include "CEmitter.h"

USING_NS_CC;

CEmitter::CEmitter()
{
	_Emitter = nullptr;

	_isTouch = false;
	_bEnable = false;
}

CEmitter::~CEmitter()
{

}

void CEmitter::setSprite(const std::string& pngname, cocos2d::Point pos, cocos2d::Scene& stage) {
	_Emitter = Sprite::createWithSpriteFrameName(pngname);

	_size = _Emitter->getContentSize();
	_initPos = pos;
	setPosition(pos);

	_Emitter->setVisible(false);

	stage.addChild(_Emitter, 10);
}

bool CEmitter::onTouchBegan(const cocos2d::Point& touchLoc) {
	if (_rect.containsPoint(touchLoc) && _bEnable) {
		_preLoc = touchLoc;
		_isTouch = true;
		return true;
	}
	return false;
}
bool CEmitter::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (_isTouch && _bEnable) {
		_curLoc = touchLoc;
		Point dir = _curLoc - _preLoc;
		setPosition(_curLoc + dir);
		_preLoc = _curLoc;
		return true;
	}
	return false;
}
bool CEmitter::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (_rect.containsPoint(touchLoc) && _isTouch && _bEnable) {
		_isTouch = false;
		return true;
	}
	return false;
}

void CEmitter::setPosition(cocos2d::Point pos) { 
	_pos = pos;
	_rect = Rect(_pos.x - _size.width / 2.0f, _pos.y - _size.height / 2.0f, _size.width, _size.height);
	_Emitter->setPosition(_pos);
}

void CEmitter::setEnable(bool enable) {
	_bEnable = enable;
	_Emitter->setVisible(enable);
	if(!enable)
		setPosition(_initPos);
}

cocos2d::Point CEmitter::getPosition() {
	return _pos;
}