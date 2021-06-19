#pragma once
#include"cocos2d.h"
#include"NormalBattleScene.h"
#include"MapGate.h"
#include"AllTag.h"
class Gate;
class PistolAmmo;
class Ammo;
class miniMapTab;
USING_NS_CC;
class BattleScene1 : public NormalBattleScene
{
public:
	virtual bool init();
	virtual void update(float dt);
	//void test(float dt);
	void Ammoupdate(float dt);
	bool isWall(float x, float y);
	bool isDamagingLand(float x, float y);
	
	void DeleteAmmo(float dt);
	bool onContactBegin(PhysicsContact& contact);
	void AmmoUpdate_Monster(float dt);
	void MapGateInit();
	void LandDamageUpdate(float dt);
	void LandSlowUpdate(float dt);
	void LandBurningUpdate(float dt);
	void PlayerDeatheUpdate(float dt);
	void DeleteAllAmmo();
	void inGate();



	CREATE_FUNC(BattleScene1);
private:
	std::vector<Ammo*> AmmoList;
	std::vector<Ammo*> m_monsterAmmoList;
	miniMapTab* MiniMap;
	Label* levelLabel;
};