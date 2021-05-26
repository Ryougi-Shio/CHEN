#include "Hero.h"
#include"cocos2d.h"
USING_NS_CC;
void Hero::initHeroSprite(int direction, cocos2d::Point position)
{
	this->position = position;
	sprite = Sprite::create("Hero/stand0.png");
	sprite->setPosition(position);
	this->addChild(sprite);
	auto walking = this->createAnimate(direction, "walk", 7);
	//sprite->runAction(walking);

}

Animate* Hero::createAnimate(int direction, const char* action, int num)
{
	auto m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Hero/walk.plist", "Hero/walk.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 0; i <= 3; i++)
	{
		char s[20];
		sprintf(s, "walk%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	//CCLOG("Move!");
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);

}
void Hero::heroMove(int direction)
{
	int bx = 0, by = 0;

	if (direction == 5)
		by = -2;
	else if (direction == 6)
		bx = -2;
	else if (direction == 7)
		by = 2;
	else if (direction == 8)
		bx = 2;
	else if (direction == 1)
	{
		bx = 2;
		by = -2;
	}
	else if (direction == 2)
	{
		bx = -2;
		by = -2;
	}
	else if (direction == 3)
	{
		bx = -2;
		by = 2;
	}
	else if (direction == 4)
	{
		bx = 2;
		by = 2;
	}

	if (direction >= 1 && direction <= 8)
	{
		auto move = MoveBy::create(0.01, Vec2(bx * 2, by * 2));
		sprite->runAction(move);
		//sprite->runAction(walking->clone());

	}
	else
	{
		//sprite->stopAllActions();
		//sprite->stopAction(walking);
	}

}
