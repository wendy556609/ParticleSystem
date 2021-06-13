#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"

using namespace std;

class CButton
{
public:
	bool _isOn;
	CButton();
	~CButton();

	void setSprite(const std::string& touchname, const std::string& onname, const std::string& offname , cocos2d::Point pos , cocos2d::Node& stage);
	void setIconSprite(const std::string& iconname);
	void setInit();
	void setEnable(bool enable);
	void setVisible(bool visible);
	void setIconReverse();

	bool getBtnState();
	std::string getSpriteName();

	void switchBtn();

	bool onTouchBegan(const cocos2d::Point& touchLoc);
	bool onTouchMoved(const cocos2d::Point& touchLoc); //觸碰移動事件
	bool onTouchEnded(const cocos2d::Point& touchLoc); //觸碰結束事件 
private:
	cocos2d::Node* _Btn;
	cocos2d::Sprite* _touchSprite;
	cocos2d::Sprite* _onSprite;
	cocos2d::Sprite* _offSprite;

	cocos2d::Sprite* _iconSprite;
	std::string _iconName;

	cocos2d::Point _pos;
	cocos2d::Size _size;
	cocos2d::Rect _rect;

	bool _isTouch;
	bool _switchOn;
	bool _enable;
	bool _visible;
};