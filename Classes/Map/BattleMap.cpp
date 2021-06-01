#include"BattleMap.h"
#include"CloseMonster_1.h"
bool BattleMap::init()
{
	int i = rand() % 3;
	CCLOG("%d",i);
	char s[40];
	sprintf(s, "maps/BattleScene%d.tmx", i);
	m_map = TMXTiledMap::create(s);
	this->addChild(m_map);
	return 1;
}

void BattleMap::bindScene(NormalBattleScene* scene)
{
	m_scene = scene;
}

TMXTiledMap* BattleMap::getBattleMap()
{
	return m_map;
}

Vector<Monster*> BattleMap::getMonster()
{
	return Vector<Monster*>(m_monster);
}

void BattleMap::createMonster()
{
	m_monster.pushBack(CloseMonster_1::create());
	m_monster.back()->bindScene(m_scene);
	m_monster.back()->Birth("Monster_birth1");
	m_monster.back()->setTag(1);
	this->addChild(m_monster.back());
}
