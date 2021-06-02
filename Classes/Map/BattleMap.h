#pragma once
#include"cocos2d.h"
#include"Monster.h"
#include"MonsterPistolAmmo.h"
class NormalBattleScene;
USING_NS_CC;
class BattleMap :public Node
{
public:
	virtual bool init();
	void createMonster();
	void bindScene(NormalBattleScene* scene);
	virtual void MonsterUpdate(float dt);
	TMXTiledMap* getBattleMap();
	Vector<Monster*> getMonster();


	CREATE_FUNC(BattleMap);
private:
	TMXTiledMap* m_map;
	Vector<Monster*> m_monster;

	NormalBattleScene* m_scene;
};