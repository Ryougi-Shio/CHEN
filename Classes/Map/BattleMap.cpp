#include"BattleMap.h"
#include"CloseMonster.h"
#include"RemoteMonster.h"
#include"Monster.h"
#include"TreasureBoxes.h"
#include"HealingVial.h"
#include"NormalBattleScene.h"
#include"Player.h"
#include"PlayerMove.h"
bool BattleMap::init()
{
	int i = rand() % 3;
//	CCLOG("%d",i);
	char s[40];
	sprintf(s, "maps/DungeonScene%d.tmx", i);
	m_map = TMXTiledMap::create(s);

	m_Items.push_back(HealingVial::create());
	this->addChild(m_Items.back(), 10);
	m_Items.back()->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	m_Items.back()->getSprite()->setOpacity(0);
	this->addChild(m_map);

	this->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
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
std::vector<Item*> BattleMap::getItems()
{
	return m_Items;
}
void BattleMap::ItemInit()
{

	m_Items.back()->bindPlayer(m_scene->getPlayer());

}

void BattleMap::ItemInBoxUpdate(float dt)
{


//	CCLOG("%d", m_Items.back()->getIsUsed());
	if (m_box->getIsCanSee()==1 && m_box->getIsUsed() == 1&&m_box->getIsOpen()==1 )
	{
		m_Items.back()->getSprite()->setOpacity(255);
		if(m_scene->getPlayer()->getplayermove()->getkeyMap()[EventKeyboard::KeyCode::KEY_R])
			m_Items.back()->Interact();
	}
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

