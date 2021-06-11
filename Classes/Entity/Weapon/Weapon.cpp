#include"Weapon.h"
#include"cocos2d.h"
#include"Pistol.h"
#include"Player/Player.h"
USING_NS_CC;
void Weapon::picked()
{
	this->removeFromParentAndCleanup(0);
}
void Weapon::bindPlayer(Player* player)
{
	mplayer = player;
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
