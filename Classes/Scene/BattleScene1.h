#pragma once
#include"cocos2d.h"
#include"NormalBattleScene.h"
#include"MapGate.h"
class Gate;
class PistolAmmo;
class Ammo;
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
	void AmmoUpdate_Monster(float dt);
	void MapGateInit();
	enum MyTag
	{
		Player_TAG,
		Monster_TAG,
		PlayerAmmo_TAG,
		PlayerAmmo_Sword_TAG,
		MonsterAmmo_TAG
	};
	void inGate();
	CREATE_FUNC(BattleScene1);
private:
	std::vector<Ammo*> AmmoList;
	std::vector<MonsterPistolAmmo*> m_monsterPistolAmmoList;
	Vector<MapGate*>m_mapgate;
};