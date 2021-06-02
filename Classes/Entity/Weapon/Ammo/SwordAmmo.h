#pragma once
#include"Entity.h"
#include"cocos2d.h"
#include"Ammo.h"

USING_NS_CC;
class SwordAmmo :public Ammo
{
public:
	virtual bool init();
	float speed = 500.0f;


	CREATE_FUNC(SwordAmmo);
private:

};