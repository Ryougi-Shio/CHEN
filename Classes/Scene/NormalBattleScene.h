#pragma once
#include"cocos2d.h"
#include"Map/BattleMap.h"
#include"MapGate.h"
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
	void Mapinit();
	bool isConnected(int obstacle);
	int getStartRoom();
	int getBossRoom();
	int getShopRoom();
	int getHidRoom();
	Vector<MapGate*> getMapGate();
	Vector<BattleMap*>getBattleMap();
	int getBattleLevel();
private:
	MusicManager* m_musicManager;
	Player* m_player;
	bool virtualMap[16];
	int start_num;
	int boss_num;
	int shop_num;
	int hid_num;
	
protected:
	Vector<BattleMap*> m_battleMap;
	BattleMap* parentMap;
	WeaponManager* m_weaponManager;
	Vector<MapGate*>m_mapgate;
	std::queue<EventKeyboard::KeyCode> cheats;
	static int level;
};