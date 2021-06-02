#pragma once
#include"cocos2d.h"
#include"Map/BattleMap.h"
class MusicManager;
class Player;
USING_NS_CC;
class NormalBattleScene : public Scene
{
public:
	MusicManager* getmusicManager();
	void bindPlayer(Player* player);
	Player* getPlayer();
	BattleMap* getParentMap();
	void changeMap(int x);
private:
	MusicManager* m_musicManager;
	Player* m_player;
protected:
	Vector<BattleMap*> m_battleMap;
	BattleMap* parentMap;
};