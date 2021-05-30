#pragma once
#include"NormalScene.h"
#include"Player.h"
#include"Gate.h"
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
class BattleScene:public NormalScene
{
public:
	virtual bool init();
	virtual void update(float dt);
	void test(float dt);
	CREATE_FUNC(BattleScene);
private:
	TMXTiledMap* map;
	Gate* safeGate;
	CloseMonster_1* Monster_1;
};