#pragma once
#include"cocos2d.h"
#include"music/music.h"
USING_NS_CC;
class Player;
/*ͨ�ó����࣬������ʵ��
* ����
* 1:���ֹ�����
* 2����TiledMap
* 3:��player
*/
class NormalScene :public cocos2d::Scene
{
public:
	MusicManager* getmusicManager();
	TMXTiledMap* getMap();
	void bindTiledMap(TMXTiledMap* map);
	void bindPlayer(Player* player);
	Player* getPlayer();
private:
	MusicManager* m_musicManager;
	TMXTiledMap* m_map;
	Player* m_player;
};
