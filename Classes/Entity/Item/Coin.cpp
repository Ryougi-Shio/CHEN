#include"Coin.h"
#include"cocos2d.h"
#include"Player.h"
#include"PlayerAttribute.h"
USING_NS_CC;
bool  Coin::init()
{
	this->bindSprite(Sprite::create("Items/coin_1.png")); 
	Animation* animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "Items/coin_%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}

	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);

	auto* action = Animate::create(animation);
	action->retain();
	this->getSprite()->runAction(action);

	return 1;
}
void Coin::Interact(int mode)
{
	mPlayer->getPlayerAttribute()->AddMoney(10);
	isUsed = 1;
	isCanSee = 1;
}
void Coin::update(float dt)
{
	;
}