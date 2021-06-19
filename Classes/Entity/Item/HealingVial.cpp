#include"HealingVial.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"AllTag.h"
#include"BattleMap.h"
USING_NS_CC;
bool HealingVial::init()
{
	this->bindSprite(Sprite::create("Items/HealingVial.png"));
	return 1;
}
void  HealingVial::Interact(int mode)
{
	if (mode == 0)//白给
	{
		if (isAround(50))
		{
			if (isUsed == 0)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVial.png"));
				mPlayer->getPlayerAttribute()->AddHp(10);//回血
			}
		}
	}
	if (mode == 1)//商店里花钱买的
	{
		if (isAround(50))
		{
			if (isUsed == 0&&mPlayer->getPlayerAttribute()->getMoney()>=30)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyVial.png"));
				mPlayer->getPlayerAttribute()->AddHp(10);
				mPlayer->getPlayerAttribute()->CutMoney(30);
			}
		}
	}
}
void HealingVial::update(float dt)
{
	;
}
void HealingVial::notice(char s[])
{
	s = "HP Healing";
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(0);
	noticeLabel->setPosition(getPosition().x, getPosition().y - noticeLabel->getContentSize().height * 1.5);
}