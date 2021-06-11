#pragma once
#include"NormalScene.h"
#include"Player.h"
#include"Gate.h"
class HeroNPC;
USING_NS_CC;
/*
* 家
* 包含
* 传送门
* 玩家
*/
class SafeScene : public NormalScene
{
public:
	
	virtual bool init();
	virtual void update(float dt);
	void ChangeHeroUpdate(float dt);
	void test(float dt);
	CREATE_FUNC(SafeScene);
private:
	TMXTiledMap* map;
	Gate* safeGate;
	HeroNPC* heroNPC;
};