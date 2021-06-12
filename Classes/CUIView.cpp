#include "CUIView.h"

using namespace cocos2d::ui;

USING_NS_CC;

CUIView::CUIView() {
	_ParticleSystem = nullptr;
	_uiRoot = nullptr;
	_stage = nullptr;
	_GravityBMValue = nullptr;
	_SpreadBMValue = nullptr;
	_DirectionBMValue = nullptr;
	_SpeedBMValue = nullptr;
	_TypeBMValue = nullptr;
	_OpacityBMValue = nullptr;
	_WindDirBMValue = nullptr;
	_WindForceBMValue = nullptr;
	
	_BtnGroup = nullptr;
	_bEmitterOn = false;
}

CUIView::~CUIView() {
}

void CUIView::setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage) {
	_uiRoot = CSLoader::createNode(uicsbname);
	stage.addChild(_uiRoot);
	_size = vsize;
	init(stage);
}

void CUIView::init(cocos2d::Scene& stage) {
	CButtonGroup::getInstance()->init(*_uiRoot, stage);
	_BtnGroup = CButtonGroup::getInstance();

	_Emitter = CEmitter::getInstance();
	_Emitter->setSprite("emittericon.png", Point(_size.width / 2, _size.height / 2), stage);

	auto* GravitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Gravity"));
    GravitySlider->addEventListener(CC_CALLBACK_2(CUIView::GravityEvent, this));
	GravitySlider->setMaxPercent(100);
	_GravityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GravityBMFont"));

	auto* SpreadSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spread"));
	SpreadSlider->addEventListener(CC_CALLBACK_2(CUIView::SpreadEvent, this));
	SpreadSlider->setMaxPercent(100);
	_SpreadBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpreadBMFont"));

	auto* DirectionSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Direction"));
	DirectionSlider->addEventListener(CC_CALLBACK_2(CUIView::DirectionEvent, this));
	DirectionSlider->setMaxPercent(100);
	_DirectionBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("DirectionBMFont"));
	
	auto* SpinSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spin"));
	SpinSlider->addEventListener(CC_CALLBACK_2(CUIView::SpinEvent, this));
	SpinSlider->setMaxPercent(100);
	_SpinBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpinBMFont"));

	auto* OpacitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Opacity"));
	OpacitySlider->addEventListener(CC_CALLBACK_2(CUIView::OpacityEvent, this));
	OpacitySlider->setMaxPercent(100);
	_OpacityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("OpacityBMFont"));

	auto* ParticlesSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Particles"));
	ParticlesSlider->addEventListener(CC_CALLBACK_2(CUIView::ParticlesEvent, this));
	ParticlesSlider->setMaxPercent(100);
	_ParticlesBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("ParticlesBMFont"));

	auto* SpeedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Speed"));
	SpeedSlider->addEventListener(CC_CALLBACK_2(CUIView::SpeedEvent, this));
	SpeedSlider->setMaxPercent(100);
	_SpeedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpeedBMFont"));

	auto* LifetimeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Lifetime"));
	LifetimeSlider->addEventListener(CC_CALLBACK_2(CUIView::LifetimeEvent, this));
	LifetimeSlider->setMaxPercent(100);
	_LifetimeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("LifetimeBMFont"));

	auto* RedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Red"));
	RedSlider->addEventListener(CC_CALLBACK_2(CUIView::RedEvent, this));
	RedSlider->setMaxPercent(100);
	_RedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("RedBMFont"));

	auto* GreenSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Green"));
	GreenSlider->addEventListener(CC_CALLBACK_2(CUIView::GreenEvent, this));
	GreenSlider->setMaxPercent(100);
	_GreenBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GreenBMFont"));

	auto* BlueSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Blue"));
	BlueSlider->addEventListener(CC_CALLBACK_2(CUIView::BlueEvent, this));
	BlueSlider->setMaxPercent(100);
	_BlueBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("BlueBMFont"));

	auto* WindDirSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_WindDirection"));
	WindDirSlider->addEventListener(CC_CALLBACK_2(CUIView::WindDirEvent, this));
	WindDirSlider->setMaxPercent(100);
	_WindDirBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("WindDirectionBMFont"));

	auto* WindForceSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_WindForce"));
	WindForceSlider->addEventListener(CC_CALLBACK_2(CUIView::WindForceEvent, this));
	WindForceSlider->setMaxPercent(100);
	_WindForceBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("WindForceBMFont"));

	auto* TypeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Type"));
	TypeSlider->addEventListener(CC_CALLBACK_2(CUIView::TypeEvent, this));
	TypeSlider->setMaxPercent(100);
	_TypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("TypeBMFont"));
}

void CUIView::setTarget(CParticleSystem& ParticleSystem) {
	_ParticleSystem = &ParticleSystem;
	_ParticleSystem->setGravity(0);
	_ParticleSystem->setSpread(180);
	_ParticleSystem->setDirection(0);
	_ParticleSystem->setSpin(0);
	_ParticleSystem->setOpacity(255);
	_ParticleSystem->setSpeed(0);
	_ParticleSystem->setLifetime(3.5f);
	_ParticleSystem->setRed(255);
	_ParticleSystem->setGreen(255);
	_ParticleSystem->setBlue(255);
	_ParticleSystem->setWindDir(0);
	_ParticleSystem->setWindForce(0);
	_ParticleSystem->setSprite(_BtnGroup->getBtnSprite());
	
	_ParticleSystem->_fTime = 0;
	_ParticleSystem->_iTotEmitterNum = 100;
	_ParticleSystem->_iCurEmitterNum = 0;
}

void CUIView::update(float dt) {
	if (_ParticleSystem->_bModeEnd) {
		_ParticleSystem->setMode(_BtnGroup->getBtnMode());
		_ParticleSystem->setEmitterPos(_Emitter->getPosition());
	}
	_ParticleSystem->update(dt);
}

void CUIView::onTouchBegan(const cocos2d::Point& touchLoc) {
	if (!_BtnGroup->onTouchBegan(touchLoc) && !_bEmitterOn)
		_ParticleSystem->onTouchBegan(touchLoc);

	_Emitter->onTouchBegan(touchLoc);
}

void CUIView::onTouchMoved(const cocos2d::Point& touchLoc) {
	if (!_BtnGroup->onTouchMoved(touchLoc) && !_bEmitterOn)
		_ParticleSystem->onTouchMoved(touchLoc);

	if (_Emitter->onTouchMoved(touchLoc))
		_ParticleSystem->setEmitterPos(_Emitter->getPosition());
}

void CUIView::onTouchEnded(const cocos2d::Point& touchLoc) {
	if (!_BtnGroup->onTouchEnded(touchLoc) && !_bEmitterOn)
		_ParticleSystem->onTouchEnded(touchLoc);

	if (_BtnGroup->getBtnState(STYLEBTN))
		_ParticleSystem->setSprite(_BtnGroup->getBtnSprite());

	_bEmitterOn = _BtnGroup->getBtnState(EMITTERBTN);
	_Emitter->setEnable(_bEmitterOn);
	_ParticleSystem->onEmitter(_bEmitterOn);
	
	if (_bEmitterOn) {
		if (_BtnGroup->getBtnState(MODEBTN))
			_Emitter->setType(_BtnGroup->getBtnMode());
		_ParticleSystem->setEmitterPos(_Emitter->getPosition());
	}
		
	if (_Emitter->onTouchEnded(touchLoc))
		_ParticleSystem->setEmitterPos(_Emitter->getPosition());
}

void CUIView::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		int iType = persent / 20;
		_TypeBMValue->setString(StringUtils::format("%d", iType));
		_ParticleSystem->setType(iType);
	}
}

void CUIView::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fGravity = (-50.0f + persent) / 5.0f;
		_GravityBMValue->setString(StringUtils::format("%2.1f", fGravity));
		_ParticleSystem->setGravity(fGravity);
	}
}

void CUIView::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fSpread = persent * 1.8f;
		_SpreadBMValue->setString(StringUtils::format("%2.0f", fSpread));
		_ParticleSystem->setSpread(fSpread);
	}
}

void CUIView::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fDirection = persent * 3.6f;
		_DirectionBMValue->setString(StringUtils::format("%2.0f", fDirection));
		_ParticleSystem->setDirection(fDirection);
	}
}

void CUIView::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fSpin = persent * 3.6f;
		_SpinBMValue->setString(StringUtils::format("%2.0f", fSpin));
		_ParticleSystem->setSpin(fSpin);
	}
}

void CUIView::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fOpacity = persent * 2.55f;
		_OpacityBMValue->setString(StringUtils::format("%2.0f", fOpacity));
		_ParticleSystem->setOpacity(fOpacity);
	}
}

void CUIView::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fNumber = persent * 1.99f + 1.0f;
		_ParticlesBMValue->setString(StringUtils::format("%2.0f", fNumber));
		_ParticleSystem->setNumber(fNumber);
	}
}

void CUIView::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fSpeed = persent / 2.5f;
		_SpeedBMValue->setString(StringUtils::format("%2.0f", fSpeed));
		_ParticleSystem->setSpeed(fSpeed);
	}
}

void CUIView::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fLifetime = persent * 0.04f + 1.0f;
		_LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
		_ParticleSystem->setLifetime(fLifetime);
	}
}

void CUIView::RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fRed = persent * 2.55f;
		_RedBMValue->setString(StringUtils::format("%2.0f", fRed));
		_ParticleSystem->setRed(fRed);
	}
}

void CUIView::GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fGreen = persent * 2.55f;
		_GreenBMValue->setString(StringUtils::format("%2.0f", fGreen));
		_ParticleSystem->setGreen(fGreen);
	}
}

void CUIView::BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fBlue = persent * 2.55f;
		_BlueBMValue->setString(StringUtils::format("%2.0f", fBlue));
		_ParticleSystem->setBlue(fBlue);
	}
}

void CUIView::WindDirEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fWindDir = persent * 3.6f;
		_WindDirBMValue->setString(StringUtils::format("%2.0f", fWindDir));
		_ParticleSystem->setWindDir(fWindDir);
	}
}

void CUIView::WindForceEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		const Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
		int persent = slider->getPercent();
		float fWindForce = persent / 10.0f;
		_WindForceBMValue->setString(StringUtils::format("%2.0f", fWindForce));
		_ParticleSystem->setWindForce(fWindForce);
	}
}