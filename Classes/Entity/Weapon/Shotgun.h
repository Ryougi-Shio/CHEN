#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#include"Weapon.h"
class Player;
class Ammo;
USING_NS_CC;
class Shotgun : public Weapon
{
public:
	virtual bool init();
	virtual void update(float dt);
	void initground();
	virtual Ammo* Attack();


	CREATE_FUNC(Shotgun);
private:
};