#pragma once
#include"cocos2d.h"
#include"music/music.h"
USING_NS_CC;
class Player;
/*通用场景类，不生成实例
* 包含
* 1:音乐管理器
* 2：绑定TiledMap
* 3:绑定player
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
