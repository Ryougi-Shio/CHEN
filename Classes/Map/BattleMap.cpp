#include"BattleMap.h"
#include"CloseMonster.h"
#include"RemoteMonster.h"
#include"Monster.h"
#include"TreasureBoxes.h"
#include"HealingVial.h"
#include"NormalBattleScene.h"
#include"Player.h"
#include"PlayerMove.h"
#include"AllTag.h"
bool BattleMap::init()
{

	this->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
	return 1;
}
void BattleMap::MapInit(int mode)
{
	if (mode == 0)//战斗房间
	{
		int i = rand() % 3;
		char s[40];
		sprintf(s, "maps/DungeonScene%d.tmx", i);
		m_map = TMXTiledMap::create(s);
		m_map->setTag(NormalRoom_TAG);
		this->addChild(m_map);
	}
	if (mode == 1)//商店房间 
	{
		m_map = TMXTiledMap::create("maps/ShopScene.tmx");
		m_map->setTag(ShopRoom_TAG);
		this->addChild(m_map);
	}

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
std::vector <TreasureBoxes*> BattleMap::getBox()
{
	return m_box;
}
std::vector<Item*> BattleMap::getItems()
{
	return m_Items;
}
void BattleMap::BoxInit()
{
	m_box.push_back(TreasureBoxes::create());

}
void BattleMap::ItemInit()
{
	m_Items.push_back(HealingVial::create());


}
void BattleMap::BoxCreate()
{
	m_box.back()->setTag(TreasureBox_TAG);
	m_box.back()->bindMap(this);
	m_box.back()->bindPlayer(m_scene->getPlayer());
	this->addChild(m_box.back(), 1);
}
void BattleMap::ItemCreate()
{
	this->addChild(m_Items.back(), 10);
	m_Items.back()->setPosition(Vec2(this->getBox().back()->getPosition()));
	m_Items.back()->getSprite()->setOpacity(0);
	m_Items.back()->bindPlayer(m_scene->getPlayer());
	m_Items.back()->bindMap(this);
}
void BattleMap::ItemInBoxUpdate(float dt)
{

	for (int i = 0; i < m_box.size(); i++)
	{
		if (m_box.at(i)->getIsCanSee() == 1 && m_box.at(i)->getIsUsed() == 1 && m_box.at(i)->getIsOpen() == 1)
		{
			m_Items.at(i)->getSprite()->setOpacity(255);
			if (m_scene->getPlayer()->getplayermove()->getkeyMap()[EventKeyboard::KeyCode::KEY_R])
				m_Items.at(i)->Interact();
		}
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


