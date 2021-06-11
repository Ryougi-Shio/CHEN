#include"NormalScene.h"
#include"Player.h";
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

void NormalScene::bindPlayer(Player* player)
{
	m_player = player;
}

Player* NormalScene::getPlayer()
{
	return m_player;
}
TMXTiledMap* NormalScene::getMap()
{
	return m_map;
}