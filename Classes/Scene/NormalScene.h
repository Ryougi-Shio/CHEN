#pragma once
#include"cocos2d.h"
#include"music/music.h"
USING_NS_CC;
/*通用场景类，不生成实例
* 包含
* 1:音乐管理器
* 2：绑定TiledMap
*/
class NormalScene :public cocos2d::Scene
{
public:
	MusicManager* getmusicManager();
	void bindTiledMap(TMXTiledMap* map);
private:
	MusicManager* m_musicManager;
	TMXTiledMap* m_map;
};
