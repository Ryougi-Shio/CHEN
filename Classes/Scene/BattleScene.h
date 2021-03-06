#pragma once
#include"NormalBattleScene.h"
#include"Player.h"
#include"Gate.h"
#include"Ammo/PistolAmmo.h"

class CloseMonster_1;

USING_NS_CC;
/*
*战斗的地图
* 需求：
*肉鸽的随机地图生成
*（随机？）敌人
*完成关卡后出现传送门进入下一关
*可交互对象，如陷阱、强化药剂、购买物品、宝箱
*/
class BattleScene:public NormalBattleScene
{
public:
	virtual bool init();
	virtual void update(float dt);
	void test(float dt);
	void Ammoupdate(float dt);
	bool isWall(float x, float y);
	void DeleteAmmo(float dt);
	bool onContactBegin(PhysicsContact& contact);
	CREATE_FUNC(BattleScene);
private:
	Gate* safeGate;
	CloseMonster_1* Monster_1;
	std::vector<PistolAmmo*> AmmoList;
};