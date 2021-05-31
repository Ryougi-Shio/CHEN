#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
class Player;
class PistolAmmo;
USING_NS_CC;
class Weapon :public Entity
{
public:
	bool isAround(float x, float y);
	void bindPlayer(Player* player);
	Player* getPlayer();
	void picked();
	virtual PistolAmmo* Attack()=0	;
	void initground();
	bool getIsGround();
	float getShootSpeed();
	void setShootSpeed(float speed);
private:
	Player* mplayer;
	bool isground=0;
	float shootSpeed;
};