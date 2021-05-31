#pragma once
#include"Entity.h"
#include"cocos2d.h"
USING_NS_CC;
class PistolAmmo : public Entity
{
public:
	virtual bool init();
	const float speed = 500.0f;
	CREATE_FUNC(PistolAmmo);
private:
};