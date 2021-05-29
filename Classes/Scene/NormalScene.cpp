#include"NormalScene.h"
USING_NS_CC;
MusicManager* NormalScene::getmusicManager()
{
	return m_musicManager;
}
void NormalScene::bindTiledMap(TMXTiledMap* map)
{
	m_map = map;
	addChild(m_map);
}