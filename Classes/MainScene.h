#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio �������
#include "cocostudio/CocoStudio.h"
#include "CUIView.h"
#include "CParticleSystem.h"

class MainScene : public cocos2d::Scene
{
private:
    CUIView _uiView;
    CParticleSystem _ParticleSystem;
public:
    ~MainScene();

    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt);

    // touch �ƥ�
    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //Ĳ�I�}�l�ƥ�,�^�ǭȥ����O bool
    void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //Ĳ�I���ʨƥ�
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //Ĳ�I�����ƥ� 


    // implement the "static create()" method manually
    CREATE_FUNC(MainScene); //�i�}��w�q�F create() �����禡

};
