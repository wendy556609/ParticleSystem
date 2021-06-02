#include "MainScene.h"


#ifdef Audio_Example
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
//using namespace CocosDenshion;

MainScene::~MainScene()
{
#ifdef Audio_Example 1
    AudioEngine::end();
#endif
    this->removeAllChildren();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}


Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 載入 cocos Studio 輸出的 csb 檔
    auto rootNode = CSLoader::createNode("mainscenex.csb");
    addChild(rootNode);
    _uiView.setProperty("uiroot.csb", visibleSize, *this);
    _ParticleSystem.init(*this);
    _uiView.setTarget(_ParticleSystem);

    auto listener = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);		//加入觸碰開始事件
    listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);		//加入觸碰移動事件
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);		//加入觸碰離開事件

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::update));

    return true;
}

void MainScene::update(float dt)
{
    _uiView.update(dt);
}

bool MainScene::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    _uiView.onTouchBegan(touchLoc);
    return true;
}

void MainScene::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    _uiView.onTouchMoved(touchLoc);
}

void  MainScene::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰結束事件 
{
    Point touchLoc = pTouch->getLocation();
    _uiView.onTouchEnded(touchLoc);
}
