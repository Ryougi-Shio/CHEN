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
	void NoticeOnorOff(bool able);//��ǩ�Ƿ�ɼ�
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
	int  WeaponSpeed;//����
	bool isBought=true;
	bool canUse = true;
	Label* noticeLabel;	//��ǩ
};