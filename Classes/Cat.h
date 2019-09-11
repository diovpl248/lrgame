#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum eCatType {
	NORMAL,
	GOLDEN,
};

enum eDirection {
	LEFT,
	RIGHT,
};

class Cat
{
private:
	eCatType catType;
	eDirection direction;
	cocos2d::Sprite* sprite;
	Layer* scene;

public:
	Cat(Layer* scene, eCatType type, eDirection dir);
	~Cat();

	void Move(cocos2d::Point nextPoint);

	eCatType GetType();
	eDirection GetDirection();
	Sprite* GetSprite();
};