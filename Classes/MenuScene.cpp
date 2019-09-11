
#include "MenuScene.h"
#include "GameScene.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	srand(time(NULL));

	initBG();
	initMenu();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/menu-bgm.mp3", true);

	return true;
}

void MenuScene::initBG()
{
	auto spr = Sprite::create("menu/menu-bg.png");
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);

	auto winSize = Director::getInstance()->getWinSize();
	spr = Sprite::create("menu/menu-logo.png");
	spr->setPosition(Point(winSize.width / 2, winSize.height - (spr->getBoundingBox().size.height)));
	this->addChild(spr);
}

void MenuScene::initMenu()
{
	auto item_0 = MenuItemImage::create("menu/play-0.png", "menu/play-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto item_1 = MenuItemImage::create("menu/quit-0.png", "menu/quit-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));

	item_0->setTag(eMenuTag::TAG_MENUITEM_PLAY);
	item_1->setTag(eMenuTag::TAG_MENUITEM_QUIT);

	auto winSize = Director::getInstance()->getWinSize();

	auto menu = Menu::create(item_0, item_1, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Point(winSize.width / 2, winSize.height / 3));
	this->addChild(menu);
}

void MenuScene::menuCallback(cocos2d::Ref* pSender)
{
	auto item = (MenuItem*)pSender;

	switch (item->getTag())
	{
	case eMenuTag::TAG_MENUITEM_PLAY:
	{
		auto scene = TransitionFadeTR::create(1.0, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}

	break;
	case eMenuTag::TAG_MENUITEM_QUIT:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}