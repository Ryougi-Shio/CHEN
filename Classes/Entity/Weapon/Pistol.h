#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#include"Weapon.h"
class Player;
class PistolAmmo;
USING_NS_CC;
class Pistol : public Weapon
{
public:
	virtual bool init();
	virtual void update(float dt);
	void initground();
	virtual PistolAmmo* Attack();


	CREATE_FUNC(Pistol);
private:
};