#include "CButton.h"

USING_NS_CC;

CButton::CButton()
{
	_touchSprite = nullptr;
	_onSprite = nullptr;
	_offSprite = nullptr;
	_iconSprite = nullptr;

	_isTouch = false;
	_switchOn = false;

	_enable = true;
}

CButton::~CButton()
{

}

void CButton::setSprite(const std::string& touchname, const std::string& onname, const std::string& offname, cocos2d::Point pos, cocos2d::Scene& stage) {
	_touchSprite = Sprite::createWithSpriteFrameName(touchname);
	_onSprite = Sprite::createWithSpriteFrameName(onname);
	_offSprite = Sprite::createWithSpriteFrameName(offname);
	_Btn = Node::create();
	_pos = pos;
	_size = _touchSprite->getContentSize();
	_rect = Rect(_pos.x - _size.width / 2.0f, _pos.y - _size.height / 2.0f, _size.width, _size.height);

	_Btn->setPosition(_pos);
	_touchSprite->setPosition(Point(0, 0));
	_onSprite->setPosition(Point(0, 0));
	_offSprite->setPosition(Point(0, 0));

	_touchSprite->setVisible(false);
	_onSprite->setVisible(false);
	_offSprite->setVisible(true);

	stage.addChild(_Btn, 5);

	_Btn->addChild(_touchSprite, 5);
	_Btn->addChild(_onSprite, 5);
	_Btn->addChild(_offSprite, 5);
}

void CButton::setIconSprite(const std::string& iconname) {
	_iconSprite = Sprite::createWithSpriteFrameName(iconname);
	_iconName = iconname;
	_iconSprite->setPosition(Point(0, 0));
	_Btn->addChild(_iconSprite);
}

void CButton::setInit() {
	_isTouch = true;
	_switchOn = true;
	_enable = false;

	_touchSprite->setVisible(false);
	_onSprite->setVisible(true);
	_offSprite->setVisible(false);

	_Btn->setScale(1.1f);
}

void CButton::setEnable(bool enable) {
	_enable = enable;
}

void CButton::switchBtn() {
	_isTouch = !_isTouch;
	_switchOn = !_switchOn;
	_enable = !_enable;
	if (_switchOn) {
		_touchSprite->setVisible(false);
		_onSprite->setVisible(true);
		_offSprite->setVisible(false);

		_Btn->setScale(1.1f);
	}
	else {
		_touchSprite->setVisible(false);
		_onSprite->setVisible(false);
		_offSprite->setVisible(true);

		_Btn->setScale(1.0f);
	}
}

bool CButton::onTouchBegan(const cocos2d::Point& touchLoc) {
	if (_rect.containsPoint(touchLoc)) {
		_touchSprite->setVisible(true);
		_onSprite->setVisible(false);
		_offSprite->setVisible(false);

		_Btn->setScale(1.1f);
		_isTouch = true;
		return true;
	}
	return false;
}

bool CButton::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (_isTouch) {
		if (!_rect.containsPoint(touchLoc)) {
			if (_switchOn) {
				_touchSprite->setVisible(false);
				_onSprite->setVisible(true);
				_offSprite->setVisible(false);
			}
			else {
				_touchSprite->setVisible(false);
				_onSprite->setVisible(false);
				_offSprite->setVisible(true);

				_Btn->setScale(1.0f);
			}
			_isTouch = false;
			return false;
		}
		return true;
	}
	return false;
}

bool CButton::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (_rect.containsPoint(touchLoc) && _isTouch && _enable) {
		_isTouch = false;
		_switchOn = !_switchOn;
		if (_switchOn) {
			_touchSprite->setVisible(false);
			_onSprite->setVisible(true);
			_offSprite->setVisible(false);
		}
		else {
			_touchSprite->setVisible(false);
			_onSprite->setVisible(false);
			_offSprite->setVisible(true);

			_Btn->setScale(1.0f);
		}
		return true;
	}
	return false;
}

bool CButton::getBtnState() { return _switchOn; }

std::string CButton::getSpriteName() {
	return _iconName;
}