#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#include"Weapon.h"
USING_NS_CC;
class PitchFork :public Weapon
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual Ammo* Attack();
	CREATE_FUNC(PitchFork);
private:

};