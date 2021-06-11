#include"PowerVest.h"
#include"Player.h"
#include"PlayerAttribute.h"
USING_NS_CC;
bool PowerVest::init()
{
	this->bindSprite(Sprite::create("Items/PowerVest.png"));
	return 1;
}
void  PowerVest::Interact(int mode)
{
	if (mode == 0)//°×¸ø
	{
		if (isAround(50))
		{
			if (isUsed == 0)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVest.png"));
				mPlayer->getPlayerAttribute()->changeDamage_Buff(5);
			}
		}
	}
	if (mode == 1)
	{
		if (isAround(50))
		{
			if (isUsed == 0 && mPlayer->getPlayerAttribute()->getMoney() >= 10)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVest.png"));
				mPlayer->getPlayerAttribute()->changeDamage_Buff(5);
				mPlayer->getPlayerAttribute()->CutMoney(10);
			}
		}
	}
}
void PowerVest::update(float dt)
{
	;
}
