#pragma once
#include"cocos2d.h"
#include"NormalBattleScene.h"
class Gate;
class PistolAmmo;
USING_NS_CC;
class BattleScene1 : public NormalBattleScene
{
public:
	virtual bool init();
	virtual void update(float dt);
	//void test(float dt);
	void Ammoupdate(float dt);
	bool isWall(float x, float y);
	void DeleteAmmo(float dt);
	bool onContactBegin(PhysicsContact& contact);
	CREATE_FUNC(BattleScene1);
private:
	std::vector<PistolAmmo*> AmmoList;
};