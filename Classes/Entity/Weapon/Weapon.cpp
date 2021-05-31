#include"Weapon.h"
#include"cocos2d.h"
#include"Pistol.h"
#include"Player/Player.h"
USING_NS_CC;
void Weapon::picked()
{
	if (isground)
	{
		Director::getInstance()->getRunningScene()->removeChild(this);
		isground = 0;
		unscheduleUpdate();
	}
	mplayer->PistolInit();
}
bool Weapon::getIsGround()
{
	return isground;
}
void Weapon::bindPlayer(Player* player)
{
	mplayer = player;
}
Player* Weapon::getPlayer()
{
	return mplayer;
}
void Weapon::initground()
{
	isground = 1;
	Director::getInstance()->getRunningScene()->addChild(this);
	scheduleUpdate();
}

float Weapon::getShootSpeed()
{
	return shootSpeed;
}

void Weapon::setShootSpeed(float speed)
{
	shootSpeed = speed;
}