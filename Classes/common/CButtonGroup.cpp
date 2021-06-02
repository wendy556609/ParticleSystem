#include "CButtonGroup.h"

USING_NS_CC;

CButtonGroup* _SButtonGroup;

CButtonGroup::CButtonGroup() {
	_uiRoot = nullptr;

	_curStyleBtn = nullptr;
	_EmitterBtn = nullptr;
	_BubbleBtn = nullptr;
	_FlareBtn = nullptr;

	_click = false;
}

CButtonGroup::~CButtonGroup() {
	CC_SAFE_DELETE(_EmitterBtn);
	CC_SAFE_DELETE(_BubbleBtn);
}

CButtonGroup* CButtonGroup::getInstance() {
	if (_SButtonGroup == nullptr)_SButtonGroup = new(nothrow)CButtonGroup();
	return _SButtonGroup;
}

void CButtonGroup::Destroy() {
	if (_SButtonGroup != nullptr)CC_SAFE_DELETE(_SButtonGroup);
}

void CButtonGroup::init(cocos2d::Node& root, cocos2d::Scene& stage) {
	_uiRoot = &root;
	_style = FLARE;

	_EmitterBtn = new(nothrow)CButton();
	auto* loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("emitterpos"));
	loc->setVisible(false);
	_EmitterBtn->setSprite("emittertd.png", "emitteron.png", "emitteroff.png", loc->getPosition(), stage);

	_BubbleBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("bubble_Btn"));
	loc->setVisible(false);
	_BubbleBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_BubbleBtn->setIconSprite("bubble.png");

	_FlareBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("flare_Btn"));
	loc->setVisible(false);
	_FlareBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_FlareBtn->setIconSprite("flare.png");
	_FlareBtn->setInit();

	_curStyleBtn = _FlareBtn;
}

bool CButtonGroup::getBtnState(int type) {
	switch (type)
	{
	case EMITTERBTN:
		return _EmitterBtn->getBtnState();
		break;
	case STYLEBTN:
		if (_FlareBtn->getBtnState()) {
			_style = FLARE;
			return true;
		}
		else if (_BubbleBtn->getBtnState()) {
			_style = BUBBLE;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

std::string CButtonGroup::getBtnSprite() {
	switch (_style)
	{
	case FLARE:
		return _FlareBtn->getSpriteName();
		break;
	case BUBBLE:
		return _BubbleBtn->getSpriteName();
		break;
	default:
		break;
	}
	return _FlareBtn->getSpriteName();
}

bool CButtonGroup::onTouchBegan(const cocos2d::Point& touchLoc) {
	if (_EmitterBtn->onTouchBegan(touchLoc)) {
		_click = true;
		return true;
	}

	if (_FlareBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_BubbleBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	return false;
}

bool CButtonGroup::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (_EmitterBtn->onTouchMoved(touchLoc)) {
		return true;
	}

	if (_FlareBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_BubbleBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	return false;
}

bool CButtonGroup::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (_EmitterBtn->onTouchEnded(touchLoc)) {
		_click = false;
		return true;
	}

	if (_FlareBtn->onTouchEnded(touchLoc)) {
		_FlareBtn->setEnable(false);
		if(_curStyleBtn!= _FlareBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _FlareBtn;
		return true;
	}
	else if (_BubbleBtn->onTouchEnded(touchLoc)) {
		_BubbleBtn->setEnable(false);
		if (_curStyleBtn != _BubbleBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _BubbleBtn;
		return true;
	}
	return false;
}