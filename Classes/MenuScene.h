#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

enum eMenuTag {
	TAG_MENUITEM_PLAY,
	TAG_MENUITEM_QUIT,
};

class MenuScene : public Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	void initBG();
	void initMenu();

    void menuCallback(cocos2d::Ref* pSender);
};

#endif
