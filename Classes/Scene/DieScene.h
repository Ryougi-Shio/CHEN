#pragma once
#include"cocos2d.h"
USING_NS_CC;
class DieScene :public Scene
{
public:
	virtual bool init();
	void remove(float dt);
	CREATE_FUNC(DieScene);
};