#include"ShieldBattery.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"AllTag.h"
#include"BattleMap.h"
USING_NS_CC;
bool ShieldBattery::init()
{
	this->bindSprite(Sprite::create("Items/ShieldBattery.png"));
	return 1;
}
void  ShieldBattery::Interact(int mode)
{
	if (mode == 0)//°×¸ø
	{
		if (isAround(50))
		{
			if (isUsed == 0)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyBattery.png"));
				mPlayer->getPlayerAttribute()->changeAp(20);
				mPlayer->getPlayerAttribute()->AddHp(1);
			}
		}
	}
	if (mode == 1)
	{
		if (isAround(100))
		{
			if (isUsed == 0 && mPlayer->getPlayerAttribute()->getMoney() >= 10)
			{
				isUsed = 1;
				this->removeAllChildren();
				this->bindSprite(Sprite::create("Items/EmptyBattery.png"));
				mPlayer->getPlayerAttribute()->changeAp(20);
				mPlayer->getPlayerAttribute()->CutMoney(10);
			}
		}
	}
}
void ShieldBattery::update(float dt)
{
	;
}
void ShieldBattery::notice(char s[])
{
	s = "Shield UP";
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(0);
	noticeLabel->setPosition(getPosition().x, getPosition().y - noticeLabel->getContentSize().height * 1.5);
}