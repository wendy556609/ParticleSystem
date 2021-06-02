#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio �������
#include "cocostudio/CocoStudio.h"
#include "CParticleSystem.h"
#include "common/CButtonGroup.h"
#include "common/CEmitter.h"

class CUIView
{
private:
	CParticleSystem* _ParticleSystem;
	// �إ߱��� particle system �һݪ��ާ@����
	cocos2d::Node* _uiRoot;
	cocos2d::Scene* _stage;
	cocos2d::Size _size; //�}�Ҫ������j�p

	// ���l���i���㤣�P�Ѽƪ����
	cocos2d::ui::TextBMFont* _GravityBMValue;
	cocos2d::ui::TextBMFont* _SpreadBMValue;
	cocos2d::ui::TextBMFont* _DirectionBMValue;
	cocos2d::ui::TextBMFont* _SpinBMValue;
	cocos2d::ui::TextBMFont* _OpacityBMValue;
	cocos2d::ui::TextBMFont* _ParticlesBMValue;
	cocos2d::ui::TextBMFont* _SpeedBMValue;
	cocos2d::ui::TextBMFont* _LifetimeBMValue;
	cocos2d::ui::TextBMFont* _RedBMValue;
	cocos2d::ui::TextBMFont* _GreenBMValue;
	cocos2d::ui::TextBMFont* _BlueBMValue;

	// ��ܤ��P�����l���A�A�Φb Emitter �S���}�Ҫ����A
	cocos2d::ui::TextBMFont* _TypeBMValue;

	CButtonGroup* _BtnGroup;

	bool _bEmitterOn;
	CEmitter* _Emitter;
public:
	CUIView();
	~CUIView();

	void setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage);
	void init(cocos2d::Scene& stage);
	void setTarget(CParticleSystem& ParticleSystem);

	void update(float dt);

	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	

	// touch �ƥ�
	void onTouchBegan(const cocos2d::Point& touchLoc);
	void onTouchMoved(const cocos2d::Point& touchLoc); //Ĳ�I���ʨƥ�
	void onTouchEnded(const cocos2d::Point& touchLoc); //Ĳ�I�����ƥ�
};