#include"Weapon.h"
#include"cocos2d.h"
#include"Pistol.h"
#include"Player/Player.h"
#include"AllTag.h"
USING_NS_CC;
void Weapon::picked()
{
	this->removeFromParentAndCleanup(0);
}
void Weapon::bindPlayer(Player* player)
{
	mplayer = player;
}
void Weapon::notice(char s[])
{
	s = "$100";
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	this->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(0);
	noticeLabel->setPosition(getPosition().x, getPosition().y + noticeLabel->getContentSize().height * 1.5);
}
void Weapon::NoticeOnorOff(bool able)
{
	if(able)
		noticeLabel->setOpacity(255);
	else
		noticeLabel->setOpacity(0);
}
Player* Weapon::getPlayer()
{
	return mplayer;
}

int  Weapon::getWeaponSpeed()
{
	return WeaponSpeed;
}

void Weapon::setWeaponSpeed(int  speed)
{
	WeaponSpeed = speed;
}

bool Weapon::getIsBought()
{
	return isBought;
}

void Weapon::setIsBought(bool is)
{
	isBought = is;
}

bool Weapon::getCanUse()
{
	return canUse;
}

void Weapon::setCanUse(bool can)
{
	canUse = can;
}

bool Weapon::isAround()
{
	float Px = mplayer->getPositionX();
	float Py = mplayer->getPositionY();
	float x = this->getPositionX();
	float y = this->getPositionY();
	if (sqrt((Px - x) * (Px - x) + (Py - y) * (Py - y)) <= 100)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
