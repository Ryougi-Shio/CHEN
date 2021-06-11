#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
class Player;
class Ammo;
USING_NS_CC;
class Weapon :public Entity
{
public:
	bool isAround();
	void bindPlayer(Player* player);
	Player* getPlayer();
	void picked();
	virtual Ammo* Attack()=0;
	int  getWeaponSpeed();
	void setWeaponSpeed(int  speed);


private:
	Player* mplayer;
	int  WeaponSpeed;//…‰ÀŸ
};