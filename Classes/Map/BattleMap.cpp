#include"BattleMap.h"
#include"CloseMonster.h"
#include"RemoteMonster.h"
#include"Monster.h"
#include"TreasureBoxes.h"
bool BattleMap::init()
{
	int i = rand() % 3;
//	CCLOG("%d",i);
	char s[40];
	sprintf(s, "maps/DungeonScene%d.tmx", i);
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
TreasureBoxes* BattleMap::getBox()
{
	return m_box;
}
void BattleMap::createMonster(int MonsterNum)
{

	char s1[30] = "O_small_monster";
	char s2[30] = "pig_monster";
	char s3[30] = "snow_monster";
	char s4[30] = "Y_craw_monster";

	for (int i = 0; i < MonsterNum; i++)
	{
		char Monster_name[30];
		int Monster_type = rand()%4+1;
		
		if (Monster_type == 1)
		{
			strcpy(Monster_name,s1);
			m_monster.pushBack(RemoteMonster::create());
			m_monster.back()->setTag(AllTag::O_small_monster_TAG);
		}
		else if(Monster_type == 2)
		{
			strcpy(Monster_name, s2);
			m_monster.pushBack(CloseMonster::create());
			m_monster.back()->setTag(AllTag::pig_monster_TAG);
		}
		else if (Monster_type == 3)
		{
			strcpy(Monster_name, s3);
			m_monster.pushBack(CloseMonster::create());
			m_monster.back()->setTag(AllTag::snow_monster_TAG);
		}
		else if (Monster_type == 4)
		{
			strcpy(Monster_name, s4);
			m_monster.pushBack(RemoteMonster::create());
			m_monster.back()->setTag(AllTag::Y_craw_monster_TAG);
		}


		m_monster.back()->InitWithName(Monster_name);
		m_monster.back()->FramCacheInit(Monster_name);
		m_monster.back()->bindScene(m_scene);
		m_monster.back()->Birth(i+1);
//		m_monster.back()->setTag(1);
		this->addChild(m_monster.back());

	}


}

void BattleMap::MonsterUpdate(float dt)
{


}
int BattleMap::getNumber()
{
	return Number;
}
void BattleMap::setNumber(int i)
{
	Number = i;
}
void BattleMap::BoxInit()
{
	m_box = TreasureBoxes::create();

}

