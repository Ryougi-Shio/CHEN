#include"PowerVest.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"AllTag.h"
#include"BattleMap.h"
USING_NS_CC;
bool PowerVest::init()
{
	this->bindSprite(Sprite::create("Items/PowerVest.png"));

	return 1;
}
void  PowerVest::Interact(int mode)
{
	if (mode == 0)//白给
	{
		if (isAround(50))
		{
			if (isUsed == 0)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVest.png"));
				mPlayer->getPlayerAttribute()->changeDamage_Buff(1);//增加伤害buff

			}
		}
	}
	if (mode == 1)
	{
		if (isAround(50))
		{
			if (isUsed == 0 && mPlayer->getPlayerAttribute()->getMoney() >= 30)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVest.png"));
				mPlayer->getPlayerAttribute()->changeDamage_Buff(1);
				mPlayer->getPlayerAttribute()->CutMoney(30);
			}
		}
	}
}
//Notice的初始化 
void PowerVest::notice(char s[])
{

	s = "Damage UP";
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(0);
	noticeLabel->setPosition(getPosition().x, getPosition().y - noticeLabel->getContentSize().height * 1.5);
	

}

void PowerVest::update(float dt)
{
	;
}
