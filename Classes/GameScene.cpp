
#include "GameScene.h"
#include "MenuScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	initBG();

	initData();
	initTopMenuLabel();
	initMenu();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/game-bgm.wav", true);

	showCats();

	return true;
}

void GameScene::initMenu()
{
	auto item = MenuItemImage::create("menu/main-0.png", "menu/main-1.png", CC_CALLBACK_1(GameScene::menuCallback, this));

	auto menu = Menu::create(item, NULL);
	menu->setPosition(Point(winSize.width / 2, winSize.height / 3));
	menu->setVisible(false);
	menu->setTag(eGameTag::TAG_MENU);
	this->addChild(menu,9999);

	auto menuBG = LayerColor::create(Color4B(0,0,0,180));
	menuBG->setVisible(false);
	menuBG->setTag(eGameTag::TAG_MENU_BG);
	this->addChild(menuBG, 9998);

	TTFConfig ttfConfig("fonts/Changa-Bold.ttf", 50);
	ttfConfig.outlineSize = 2;

	auto scoreLabel = Label::createWithTTF(ttfConfig, "123");
	scoreLabel->setTag(eGameTag::TAG_MENU_SCORE);
	scoreLabel->setPosition(Point(winSize.width/2, winSize.height/2 + 20));
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->enableOutline(Color4B::BLACK);
	scoreLabel->setVisible(false);
	this->addChild(scoreLabel,10000);
}

void GameScene::initData()
{
	winSize = Director::getInstance()->getWinSize();

	score = 0;
	life = MAX_LIFE;

	for (int i = 0; i < MAX_CATS; i++)
	{
		addNewCat();
	}

	lifeSprites.resize(MAX_LIFE);
}

void GameScene::initBG()
{
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	auto spr = Sprite::create("game/game-bg-tile.png");
	auto size = spr->getBoundingBox().size;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			spr = Sprite::create("game/game-bg-tile.png");
			spr->setAnchorPoint(Point(0, 0));
			spr->setPosition(i * size.width, j * size.height);
			bgLayer->addChild(spr);
		}
	}

	auto action_0 = Sequence::create(
		MoveBy::create(0.5, Point(0, size.height * -1)),
		Place::create(Point(0, 0)),
		NULL
	);

	auto action_1 = RepeatForever::create(action_0);

	bgLayer->runAction(action_1);
}

void GameScene::initTopMenuLabel()
{
	TTFConfig ttfConfig("fonts/Changa-Bold.ttf", 20);
	ttfConfig.outlineSize = 2;

	auto scoreLabel = Label::createWithTTF(ttfConfig, "");

	scoreLabel->setTag(eGameTag::LABEL_SCORE);
	scoreLabel->setAnchorPoint(Point(1, 1));
	scoreLabel->setPosition(Point(winSize.width, winSize.height));
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->enableOutline(Color4B::BLACK);
	this->addChild(scoreLabel);

	Point point = Point(0, winSize.height);
	for (auto& spr : lifeSprites)
	{
		spr = Sprite::create("life.png");
		spr->setAnchorPoint(Point(0, 1));
		spr->setPosition(point);
		point.x += spr->getBoundingBox().size.width;

		this->addChild(spr);
	}

	setLabelScore();
	setSpriteLife();
}

void GameScene::setLabelScore()
{
	auto label = (Label*)this->getChildByTag(eGameTag::LABEL_SCORE);
	label->setString(StringUtils::format("SCORE %d", score));
}

void GameScene::setSpriteLife()
{
	for (int i = 0; i < life; i++)
	{
		lifeSprites[i]->setVisible(true);
	}
	for (int i = life; i < MAX_LIFE; i++)
	{
		lifeSprites[i]->setVisible(false);
	}
}

void GameScene::addNewCat()
{
	eCatType catType = (eCatType)(rand() % (eCatType::GOLDEN + 1));
	eDirection direction = (eDirection)(rand() % (eDirection::RIGHT + 1));

	cats.push_back(new Cat(this,catType, direction));
}

Cat* GameScene::getCat()
{
	auto front = cats.front();
	cats.pop_front();
	addNewCat();
	return front;
}

void GameScene::rightTouch()
{
	actionParticle(true);

	score += 10;
	setLabelScore();
}

void GameScene::wrongTouch()
{
	actionParticle(false);

	life -= 1;
	setSpriteLife();

	if (life <= 0)
	{
		actionMenu(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

void GameScene::showCats()
{
	Point point(winSize.width / 2, winSize.height / 4);
	float scale = 2.0f;
	for (auto cat : cats)
	{
		Point nextPoint = point;
		eDirection dir = cat->GetDirection();
		auto sprite = cat->GetSprite();
		
		int sign = 1;

		switch (dir)
		{
		case eDirection::LEFT:
			sign = 1;
			break;
		case eDirection::RIGHT:
			sign = -1;
			break;
		}

		sprite->setScaleY(scale);
		sprite->setScaleX(scale * sign);
		sprite->setZOrder(scale * 100);

		cat->Move(nextPoint);
		
		scale *= 0.8;
		point.y += 40 * scale;
	}
}

void GameScene::actionParticle(bool right)
{
	if (right)
	{
		auto boom = ParticleSystemQuad::create("particles/boom-right.plist");
		boom->setPosition(Point(winSize.width / 2, winSize.height / 4));
		this->addChild(boom, 999);
	}
	else
	{
		auto boom = ParticleSystemQuad::create("particles/boom-wrong.plist");
		boom->setPosition(Point(winSize.width / 2, winSize.height / 4));
		this->addChild(boom, 999);
	}
}

void GameScene::actionMenu(bool isShow)
{
	auto menu = (Menu*)this->getChildByTag(eGameTag::TAG_MENU);
	auto menuBG = (LayerColor*)this->getChildByTag(eGameTag::TAG_MENU_BG);
	auto scoreLabel = (Label*)this->getChildByTag(eGameTag::TAG_MENU_SCORE);
	
	scoreLabel->setString(StringUtils::format("YOUR SCORE %d !", score));
	
	menu->setVisible(isShow);
	menuBG->setVisible(isShow);
	scoreLabel->setVisible(isShow);
}

void GameScene::onEnter()
{
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
	Layer::onExit();

	
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button-sfx.wav");

	auto touchPoint = touch->getLocation();

	bool isLeft = touchPoint.x < winSize.width / 2 ? true : false;

	auto cat = getCat();

	eCatType catType = cat->GetType();
	eDirection direction = cat->GetDirection();

	delete cat;

	if (isLeft)
	{
		switch (direction)
		{
		case LEFT:
			rightTouch();
			break;
		case RIGHT:
			wrongTouch();
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case LEFT:
			wrongTouch();
			break;
		case RIGHT:
			rightTouch();
			break;
		}
	}

	showCats();

	return true;
}

void GameScene::menuCallback(cocos2d::Ref* pSender)
{
	auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}