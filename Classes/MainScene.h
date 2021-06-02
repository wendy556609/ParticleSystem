#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
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

    // touch 事件
    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰開始事件,回傳值必須是 bool
    void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰移動事件
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰結束事件 


    // implement the "static create()" method manually
    CREATE_FUNC(MainScene); //展開後定義了 create() 成員函式

};
