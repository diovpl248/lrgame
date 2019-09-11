#include "Cat.h"

Cat::Cat(Layer* _scene, eCatType type, eDirection dir)
{
	catType = type;
	direction = dir;

	switch (type)
	{
	case NORMAL:
		sprite = cocos2d::Sprite::create("cat/cat.png");
		break;
	case GOLDEN:
		sprite = cocos2d::Sprite::create("cat/gold-cat.png");
		break;
	}

	scene = _scene;
	scene->addChild(sprite);
}

Cat::~Cat()
{
	scene->removeChild(sprite);
}

void Cat::Move(cocos2d::Point nextPoint)
{
	sprite->setPosition(nextPoint);
}

eCatType Cat::GetType()
{
	return catType;
}

eDirection Cat::GetDirection()
{
	return direction;
}

Sprite* Cat::GetSprite()
{
	return sprite;
}