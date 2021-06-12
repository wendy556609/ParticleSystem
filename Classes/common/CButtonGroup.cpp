#include "CButtonGroup.h"

USING_NS_CC;

CButtonGroup* _SButtonGroup;

CButtonGroup::CButtonGroup() {
	_uiRoot = nullptr;

	_curModeBtn = nullptr;
	_curStyleBtn = nullptr;
	_EmitterBtn = nullptr;

	_BubbleBtn = nullptr;
	_FlareBtn = nullptr;
	_CircleBtn = nullptr;
	_CloudBtn = nullptr;
	_SparkBtn = nullptr;

	_FireworkBtn = nullptr;
	_FireBtn = nullptr;

	_click = false;
}

CButtonGroup::~CButtonGroup() {
	CC_SAFE_DELETE(_EmitterBtn);

	CC_SAFE_DELETE(_BubbleBtn);
	CC_SAFE_DELETE(_CometBtn);
	CC_SAFE_DELETE(_FlareBtn);
	CC_SAFE_DELETE(_CircleBtn);
	CC_SAFE_DELETE(_CloudBtn);
	CC_SAFE_DELETE(_SparkBtn);

	CC_SAFE_DELETE(_FireworkBtn);
	CC_SAFE_DELETE(_FireBtn);
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

	//Particle Style
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

	_CometBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("comet_Btn"));
	loc->setVisible(false);
	_CometBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_CometBtn->setIconSprite("comet.png");

	_CircleBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("circle_Btn"));
	loc->setVisible(false);
	_CircleBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_CircleBtn->setIconSprite("circle.png");

	_CloudBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("cloud_Btn"));
	loc->setVisible(false);
	_CloudBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_CloudBtn->setIconSprite("cloud.png");

	_SparkBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("spark_Btn"));
	loc->setVisible(false);
	_SparkBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
	_SparkBtn->setIconSprite("spark.png");

	_curStyleBtn = _FlareBtn;

	//Particle Mode
	_FireworkBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("firework_Btn"));
	loc->setVisible(false);
	_FireworkBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);

	_FireBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("fire_Btn"));
	loc->setVisible(false);
	_FireBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);

	_LuckyBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("lucky_Btn"));
	loc->setVisible(false);
	_LuckyBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);

	_RainBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("rain_Btn"));
	loc->setVisible(false);
	_RainBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);

	_SnowBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("snow_Btn"));
	loc->setVisible(false);
	_SnowBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);

	_LoveBtn = new(nothrow)CButton();
	loc = dynamic_cast<cocos2d::Sprite*>(_uiRoot->getChildByName("love_Btn"));
	loc->setVisible(false);
	_LoveBtn->setSprite("runon.png", "runon.png", "runnormal.png", loc->getPosition(), stage);
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
		else if (_CometBtn->getBtnState()) {
			_style = COMET;
			return true;
		}
		else if (_CircleBtn->getBtnState()) {
			_style = Circle;
			return true;
		}
		else if (_CloudBtn->getBtnState()) {
			_style = Cloud;
			return true;
		}
		else if (_SparkBtn->getBtnState()) {
			_style = Spark;
			return true;
		}
		break;
	case MODEBTN:
		if (_FireworkBtn->getBtnState()) {
			_Mode = FIREWORKSTYLE;
		}
		else if (_FireBtn->getBtnState()) {
			_Mode = FIRE;
		}
		else if (_LuckyBtn->getBtnState()) {
			_Mode = LUCKY;
		}
		else if (_RainBtn->getBtnState()) {
			_Mode = RAIN;
		}
		else if (_SnowBtn->getBtnState()) {
			_Mode = SNOW;
		}
		else if (_LoveBtn->getBtnState()) {
			_Mode = LOVE;
		}
		else {
			_Mode = EMITTER;
		}
		return true;
		break;
	default:
		break;
	}
	return false;
}

int CButtonGroup::getBtnMode() {
	return _Mode;
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
	case COMET:
		return _CometBtn->getSpriteName();
		break;
	case Circle:
		return _CircleBtn->getSpriteName();
		break;
	case Cloud:
		return _CloudBtn->getSpriteName();
		break;
	case Spark:
		return _SparkBtn->getSpriteName();
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

	//Particle Style
	if (_FlareBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_BubbleBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_CometBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_CircleBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_CloudBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_SparkBtn->onTouchBegan(touchLoc)) {
		return true;
	}

	//Particle Mode
	if (_FireworkBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_FireBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_LuckyBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_RainBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_SnowBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	else if (_LoveBtn->onTouchBegan(touchLoc)) {
		return true;
	}
	return false;
}

bool CButtonGroup::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (_EmitterBtn->onTouchMoved(touchLoc)) {
		return true;
	}

	//Particle Style
	if (_FlareBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_BubbleBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_CometBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_CircleBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_CloudBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_SparkBtn->onTouchMoved(touchLoc)) {
		return true;
	}

	//Particle Mode
	if (_FireworkBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_FireBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_LuckyBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_RainBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_SnowBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	else if (_LoveBtn->onTouchMoved(touchLoc)) {
		return true;
	}
	return false;
}

bool CButtonGroup::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (_EmitterBtn->onTouchEnded(touchLoc)) {
		_click = false;
		return true;
	}

	//Particle Style
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
	else if (_CometBtn->onTouchEnded(touchLoc)) {
		_CometBtn->setEnable(false);
		if (_curStyleBtn != _CometBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _CometBtn;
		return true;
	}
	else if (_CircleBtn->onTouchEnded(touchLoc)) {
		_CircleBtn->setEnable(false);
		if (_curStyleBtn != _CircleBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _CircleBtn;
		return true;
	}
	else if (_CloudBtn->onTouchEnded(touchLoc)) {
		_CloudBtn->setEnable(false);
		if (_curStyleBtn != _CloudBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _CloudBtn;
		return true;
	}
	else if (_SparkBtn->onTouchEnded(touchLoc)) {
		_SparkBtn->setEnable(false);
		if (_curStyleBtn != _SparkBtn)
			_curStyleBtn->switchBtn();
		_curStyleBtn = _SparkBtn;
		return true;
	}

	//Particle Mode
	if (_FireworkBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _FireworkBtn;
		}
		else if (_curModeBtn != _FireworkBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _FireworkBtn;
		}
		else if (_curModeBtn == _FireworkBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	else if (_FireBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _FireBtn;
		}
		else if (_curModeBtn != _FireBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _FireBtn;
		}
		else if (_curModeBtn == _FireBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	else if (_LuckyBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _LuckyBtn;
		}
		else if (_curModeBtn != _LuckyBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _LuckyBtn;
		}
		else if (_curModeBtn == _LuckyBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	else if (_RainBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _RainBtn;
		}
		else if (_curModeBtn != _RainBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _RainBtn;
		}
		else if (_curModeBtn == _RainBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	else if (_SnowBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _SnowBtn;
		}
		else if (_curModeBtn != _SnowBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _SnowBtn;
		}
		else if (_curModeBtn == _SnowBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	else if (_LoveBtn->onTouchEnded(touchLoc)) {
		if (_curModeBtn == nullptr) {
			_curModeBtn = _LoveBtn;
		}
		else if (_curModeBtn != _LoveBtn && _curModeBtn != nullptr) {
			_curModeBtn->switchBtn();
			_curModeBtn->setEnable(true);
			_curModeBtn = _LoveBtn;
		}
		else if (_curModeBtn == _LoveBtn) {
			_curModeBtn = nullptr;
		}
		return true;
	}
	return false;
}