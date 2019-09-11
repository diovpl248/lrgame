#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <list>
#include <vector>

#include <Cat.h>

USING_NS_CC;
using namespace CocosDenshion;

using namespace std;

enum eGameTag {
	LABEL_SCORE,
	SPRITE_LIFE,
	TAG_MENU,
	TAG_MENU_BG,
	TAG_MENU_SCORE
};

class GameScene : public Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	CREATE_FUNC(GameScene);

private:
	Size winSize;

	const int MAX_LIFE = 3;
	const int MAX_CATS = 10;

	int life;
	int score;

	list<Cat*> cats;
	vector<Sprite*> lifeSprites;

	EventListenerTouchOneByOne* listener;

private:
	void initData();
	void initBG();
	void initTopMenuLabel();
	void initMenu();

	void setLabelScore();
	void setSpriteLife();

	void addNewCat();
	Cat* getCat();

	void rightTouch();
	void wrongTouch();

	void showCats();

	void actionParticle(bool right);
	void actionMenu(bool isShow);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual bool onTouchBegan(Touch* touch, Event* event) override;

	void menuCallback(cocos2d::Ref* pSender);
};

#endif