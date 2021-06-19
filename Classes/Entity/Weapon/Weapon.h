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
	void notice(char s[]);
	void NoticeOnorOff(bool able);//标签是否可见
	Player* getPlayer();
	void picked();
	virtual Ammo* Attack()=0;
	int  getWeaponSpeed();
	void setWeaponSpeed(int  speed);
	bool getIsBought();
	void setIsBought(bool is);
	bool getCanUse();
	void setCanUse(bool can);

private:
	Player* mplayer;
	int  WeaponSpeed;//射速
	bool isBought=true;
	bool canUse = true;
	Label* noticeLabel;	//标签
};