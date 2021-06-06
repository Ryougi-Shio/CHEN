#pragma once
#include"cocos2d.h"
#include"Monster.h"
#include"MonsterPistolAmmo.h"
#include"AllTag.h"
#include"Item.h"
class NormalBattleScene;
class TreasureBoxes;
USING_NS_CC;
class BattleMap :public Node
{
public:
	virtual bool init();

	void createMonster(int MonsterNum);
	void bindScene(NormalBattleScene* scene);
	virtual void MonsterUpdate(float dt);
	virtual void ItemInBoxUpdate(float dt);
	TMXTiledMap* getBattleMap();
	int getNumber();
	void setNumber(int i);
	Vector<Monster*> getMonster();
	TreasureBoxes* getBox();
	std::vector<Item*> getItems();
	void BoxInit();
	void ItemInit();


	CREATE_FUNC(BattleMap);
private:
	int Number;//记录地图在场景的编号
	TMXTiledMap* m_map;
	Vector<Monster*> m_monster;
	TreasureBoxes* m_box;
	std::vector<Item*>m_Items;
	NormalBattleScene* m_scene;
};