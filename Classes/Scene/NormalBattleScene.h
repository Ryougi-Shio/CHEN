#pragma once
#include"cocos2d.h"
#include"Map/BattleMap.h"
class MusicManager;
class WeaponManager;
class Player;
USING_NS_CC;
class NormalBattleScene : public Scene
{
public:
	MusicManager* getmusicManager();
	void bindPlayer(Player* player);
	Player* getPlayer();
	BattleMap* getParentMap();
	void bindWeaponManager(WeaponManager* WeaponManager);
	WeaponManager* getWeaponManager();
	void changeMap(int x);
private:
	MusicManager* m_musicManager;
	Player* m_player;
protected:
	Vector<BattleMap*> m_battleMap;
	BattleMap* parentMap;
	WeaponManager* m_weaponManager;
};