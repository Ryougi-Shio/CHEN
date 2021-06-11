#include"HealingVial.h"
#include"Player.h"
#include"PlayerAttribute.h"
USING_NS_CC;
bool HealingVial::init()
{
	this->bindSprite(Sprite::create("Items/HealingVial.png"));
	return 1;
}
void  HealingVial::Interact(int mode)
{
	if (mode == 0)//°×¸ø
	{
		if (isAround(50))
		{
			if (isUsed == 0)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVial.png"));
				mPlayer->getPlayerAttribute()->AddHp(1);
			}
		}
	}
	if (mode == 1)
	{
		if (isAround(50))
		{
			if (isUsed == 0&&mPlayer->getPlayerAttribute()->getMoney()>=10)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVial.png"));
				mPlayer->getPlayerAttribute()->AddHp(1);
				mPlayer->getPlayerAttribute()->CutMoney(10);
			}
		}
	}
}
void HealingVial::update(float dt)
{
	;
}
