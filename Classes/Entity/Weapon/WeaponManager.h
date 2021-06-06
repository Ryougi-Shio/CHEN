#pragma once
#include"cocos2d.h"
#include"AllTag.h"
class Weapon;
class Player;
USING_NS_CC;
class WeaponManager :public Node
{
public:
	virtual bool get(Weapon* Weapon1, Weapon* Weapon2);
	void bindPlayer(Player* player);
	void WeaponSwap();
	bool isBagfull();
	Weapon* pickUp(Weapon* Weapon_target);
	bool isAround(float x, float y);
	CREATE_FUNC(WeaponManager);
private:
	Weapon* Weapon_main;
	Weapon* Weapon_sub;
	Player* m_player;
};
