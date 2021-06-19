#include"BattleMap.h"
#include"CloseMonster.h"
#include"RemoteMonster.h"
#include"Monster.h"
#include"TreasureBoxes.h"
#include"HealingVial.h"
#include"PowerVest.h"
#include"NormalBattleScene.h"
#include"Player.h"
#include"PlayerMove.h"
#include"AllTag.h"
#include"Coin.h"
#include"Entity.h"
#include"ShieldBattery.h"
#include"Freeze_Trap.h"
#include"Pistol.h"
#include"Weapon.h"
#include"Sword.h"
#include"Shotgun.h"
#include"PitchFork.h"
#include"RemoteMonster_Laser.h"
#include"Laser.h"
#include"Statue.h"
bool BattleMap::init()
{
	return 1;
}
void BattleMap::MapInit(int mode)
{
	int i = rand() % 10;
	if (mode == 0)//战斗房间
	{

		char s[40];
		
		
		sprintf(s, "maps/BattleScene%d.tmx", i);
		m_map = TMXTiledMap::create(s);
		m_map->setTag(NormalRoom_TAG);
		this->addChild(m_map);
	}
	if (mode == 1)//商店房间 
	{
		m_map = TMXTiledMap::create("maps/ShopScene.tmx");
		m_map->setTag(ShopRoom_TAG);
		switch (rand()%4)
		{
		case 0:
			m_Weapon = Pistol::create();
			break;
		case 1:
			m_Weapon = Sword::create();
			break;
		case 2:
			m_Weapon = PitchFork::create();
			break;
		case 3:
			m_Weapon = Shotgun::create();
			break;
		default:
			break;
		}
		m_Weapon->setIsBought(false);

		m_Weapon->NoticeOnorOff(1);
		TMXObjectGroup* objGroup = m_map->getObjectGroup("Item");//获取对象层
		auto s = new char[40];
		sprintf(s, "Weapon_%d", 1);
		auto WeaponBirth = objGroup->getObject(s);//获取对象
		m_Weapon->setPosition(Vec2(WeaponBirth.at("x").asFloat(), WeaponBirth.at("y").asFloat()));//出生位置设置

		delete[]s;
		this->addChild(m_Weapon,5);

		this->addChild(m_map);
	}
	if (mode==2)
	{
		m_map = TMXTiledMap::create("maps/BossScene.tmx");
		m_map->setTag(BossRoom_TAG);

		switch (rand() % 4)
		{
		case 0:
			m_Weapon = Pistol::create();
			break;
		case 1:
			m_Weapon = Sword::create();
			break;
		case 2:
			m_Weapon = PitchFork::create();
			break;
		case 3:
			m_Weapon = Shotgun::create();
			break;
		default:
			break;
		}
	


		TMXObjectGroup* objGroup = m_map->getObjectGroup("Item");//获取对象层
		auto s = new char[40];
		sprintf(s, "Weapon_%d", 1);
		auto WeaponBirth = objGroup->getObject(s);//获取对象
		m_Weapon->setPosition(Vec2(WeaponBirth.at("x").asFloat(), WeaponBirth.at("y").asFloat()));//出生位置设置
		this->schedule(CC_SCHEDULE_SELECTOR(BattleMap::WeaponUpdate), 0.1f);
		delete[]s;
		this->addChild(m_Weapon, 5);
		m_Weapon->setCanUse(0);
		m_Weapon->bindPlayer(m_scene->getPlayer());
		m_Weapon->getSprite()->setOpacity(0);
		this->addChild(m_map);
	}
	if (mode == 4)
	{
		m_map = TMXTiledMap::create("maps/HiddenScene.tmx");
		m_map->setTag(HiddenRoom_TAG);
		this->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ChaosMapUpdate), 0.01f);
		this->addChild(m_map);
	}
	
}
void BattleMap::ChaosMapUpdate(float dt)
{

	int chaos_1 = rand() % 255 + 1;
	int chaos_2 = rand() % 255 + 1;
	int chaos_3 = rand() % 255 + 1;

	int chaos_x = rand() % 14 + 1;
	int chaos_y = rand() % 10 + 1;
	m_map->getLayer("ground")->getTileAt(Vec2(chaos_x, chaos_y))->setColor(Color3B(chaos_1, chaos_2, chaos_3));

}
void BattleMap::WeaponCreate(int TAG)
{
	switch (TAG)
	{
	case AllTag::PlayerWeapon_Sword_TAG:
		m_Weapon = Sword::create();
		break;
	case AllTag::PlayerWeapon_Pistol_TAG:
		m_Weapon = Pistol::create();
		break;
	case AllTag::PlayerWeapn_PitchFork_TAG:
		m_Weapon = PitchFork::create();
		break;
	case AllTag::PlayerWeapon_Shotgun_TAG:
		m_Weapon = Shotgun::create();
		break;
	default:
		break;
	}
	
	this->addChild(m_Weapon);
}
//地图自带武器的生成检测，怪清完后才有武器 
void BattleMap::WeaponUpdate(float dt)
{


	if (m_Weapon->getCanUse())
	{
		m_Weapon->getSprite()->setOpacity(255);
		this->unschedule(CC_SCHEDULE_SELECTOR(BattleMap::WeaponUpdate));
	}

	else
		m_Weapon->getSprite()->setOpacity(0);
	


	bool clear = true;
	for (auto ix : m_monster)
	{
		if (!ix->getIsDead())
			clear = false;
	}
	if (clear)
	{
		m_Weapon->setCanUse(true);

	}

}
Weapon* BattleMap::getWeapon()
{
	return m_Weapon;
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
std::vector<Item*> BattleMap::getTraps()
{
	return m_Traps;
}
std::vector<Item*> BattleMap::getStatue()
{
	return m_Statue;
}
void BattleMap::BoxInit()
{
	m_box.push_back(TreasureBoxes::create());

}
void BattleMap::ItemInit()
{
	//随机创建血瓶,力量药水,护盾电池 
	int i = rand() % 3;

	if(i==0)
		m_Items.push_back(HealingVial::create());
	else if(i==1)
		m_Items.push_back(PowerVest::create());
	else if(i==2)
		m_Items.push_back(ShieldBattery::create());

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
	m_Items.back()->notice("");
}

void BattleMap::ItemInBoxUpdate(float dt)
{
	//宝箱中的Item
	for (int i = 0; i < m_box.size(); i++)
	{
		//宝箱能看见，宝箱被使用，宝箱被打开
		if (m_box.at(i)->getIsCanSee() == 1 && m_box.at(i)->getIsUsed() == 1 && m_box.at(i)->getIsOpen() == 1)
		{
			m_Items.at(i)->getSprite()->setOpacity(255);
			//按下R
			if (m_scene->getPlayer()->getplayermove()->getkeyMap()[EventKeyboard::KeyCode::KEY_R])
			{
				if(m_map->getTag()!=ShopRoom_TAG)
					m_Items.at(i)->Interact(0);//mode：0，商店里要花钱的
				else if(m_map->getTag()==ShopRoom_TAG)
					m_Items.at(i)->Interact(1);//mode：1，战斗地图的白嫖奖励
			}
			//玩家在周围，抬头提示
			if (m_Items.at(i)->isAround(50))
			{
				m_Items.at(i)->NoticeOnorOff(1);
			}
			else
				m_Items.at(i)->NoticeOnorOff(0);

		}
		else
		{
			m_Items.at(i)->NoticeOnorOff(0);
		}
		
		if (m_box.at(i)->getIsOpen() == 0)
			m_Items.at(i)->getSprite()->setOpacity(0);
		else
			m_Items.at(i)->getSprite()->setOpacity(255);
	}

}
void BattleMap::StatueUpdate(float dt)
{
	for (auto ix : m_Statue)
	{
		if (m_scene->getPlayer()->getplayermove()->getkeyMap()[EventKeyboard::KeyCode::KEY_E]
			&&ix->isAround(100))//按E祈祷
		{
			ix->Interact(0);
		}
		if (ix->isAround(100))
		{
			ix->NoticeOnorOff(1);
		}
		else
			ix->NoticeOnorOff(0);
	}
}
void BattleMap::TrapsInit()
{
	m_Traps.push_back(Freeze_Trap::create());
}
void BattleMap::TrapsCreate(int i)
{
	m_Traps.back()->bindMap(this);
	m_Traps.back()->bindPlayer(m_scene->getPlayer());
	this->addChild(m_Traps.back(), 1);
	//对象层的使用
	TMXObjectGroup* objGroup = m_scene->getParentMap()->getBattleMap()->getObjectGroup("Traps");//获取对象层
	auto s = new char[40];
	sprintf(s, "Trap_%d", i);
	auto TrapBirth = objGroup->getObject(s);//获取对象

	m_Traps.back()->setPosition(Vec2(TrapBirth.at("x").asFloat(), TrapBirth.at("y").asFloat()));//出生位置设置
	
	delete []s;
}
void BattleMap::StatueCreate()
{
	m_Statue.back()->bindMap(this);
	m_Statue.back()->bindPlayer(m_scene->getPlayer());
	this->addChild(m_Statue.back(), 2);
	//对象层的使用
	TMXObjectGroup* objGroup = m_scene->getParentMap()->getBattleMap()->getObjectGroup("Item");//获取对象层
	auto s = new char[40];
	sprintf(s, "Statue_%d", 1);
	auto TrapBirth = objGroup->getObject(s);//获取对象

	m_Statue.back()->setPosition(Vec2(TrapBirth.at("x").asFloat(), TrapBirth.at("y").asFloat()));//出生位置设置
	m_Statue.back()->notice("$30");
	delete[]s;
}

void BattleMap::TrapsUpdate(float dt)
{
	for (int i = 0; i < m_Traps.size(); i++)
	{
		if (m_Traps.at(i)->isAround(50)&&m_Traps.at(i)->getIsUsed()==0)
		{
			m_Traps.at(i)->Interact(0);
			
		}
	}
}
void BattleMap::StatueInit()
{
	m_Statue.push_back(Statue::create());
}
void BattleMap::createMonster(int MonsterNum)
{
	if (m_map->getTag()==BossRoom_TAG)
	{
		if (MonsterNum == 0)//Boss创建
		{
			m_monster.pushBack(RemoteMonster::create());
			m_monster.back()->setTag(AllTag::CthulhuEye_Monster_TAG);
			m_monster.back()->InitWithName("Cthulhu's Eye_normal_monster");
			m_monster.back()->FramCacheInit("Cthulhu's Eye_normal_monster");
			m_monster.back()->bindScene(m_scene);
			m_monster.back()->Birth(0);

			this->addChild(m_monster.back());

		}
		else//Boss眷属创建 
		{
			for (int i = 0; i < MonsterNum; i++)
			{

				m_monster.pushBack(RemoteMonster_Laser::create());
				m_monster.back()->setTag(AllTag::LittleEye_monster_TAG);
				m_monster.back()->InitWithName("LittleEye_monster");
				m_monster.back()->FramCacheInit("LittleEye_monster");
				m_monster.back()->bindScene(m_scene);
				int x = rand() % 4;
				m_monster.back()->Birth(x);
				m_monster.back()->setScale(2);
				this->addChild(m_monster.back());
			}
		}

	}
	else if(m_map->getTag() == NormalRoom_TAG)
	{
		char s1[30] = "O_small_monster";
		char s2[30] = "pig_monster";
		char s3[30] = "snow_monster";
		char s4[30] = "Y_craw_monster";
		char s5[30] = "chaos_monster";
		for (int i = 0; i < MonsterNum; i++)
		{
			char Monster_name[30];
			int Monster_type = rand() % 4 + 1;
		//	Monster_type = 5;
			if (Monster_type == 1)
			{
				strcpy(Monster_name, s1);
				m_monster.pushBack(RemoteMonster::create());
				m_monster.back()->setTag(AllTag::O_small_monster_TAG);
			}
			else if (Monster_type == 2)
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
			else if (Monster_type == 5)
			{
				strcpy(Monster_name, s5);
				m_monster.pushBack(RemoteMonster::create());
				m_monster.back()->setTag(AllTag::Chaos_monster_TAG);
			}

			m_monster.back()->InitWithName(Monster_name);
			m_monster.back()->FramCacheInit(Monster_name);
			m_monster.back()->bindScene(m_scene);
			m_monster.back()->Birth(i+1);

			this->addChild(m_monster.back());

		}
	}
	else if (m_map->getTag() == HiddenRoom_TAG)
	{
		for (int i = 0; i < MonsterNum; i++)
		{
			m_monster.pushBack(RemoteMonster::create());
			m_monster.back()->setTag(AllTag::Chaos_monster_TAG);

			m_monster.back()->InitWithName("chaos_monster");
			m_monster.back()->FramCacheInit("chaos_monster");
			m_monster.back()->bindScene(m_scene);
			m_monster.back()->Birth(i + 1);

			this->addChild(m_monster.back());

		}
	}


}
void BattleMap::DropsInit()
{
	for (int i = 0; i < m_monster.size(); i++)
	{
		m_Drops.push_back(Coin::create());
	}

}
void BattleMap::DropsCreate(int mode)
{
	if (mode == 0)
	{
		for (int i = 0; i < m_Drops.size(); i++)
		{
			this->addChild(m_Drops.at(i), 11);
			m_Drops.at(i)->setTag(Coin_TAG);

			m_Drops.at(i)->getSprite()->setOpacity(0);
			m_Drops.at(i)->bindPlayer(m_scene->getPlayer());
			m_Drops.at(i)->bindMap(this);
		}
	}
	else if (mode == 1)
	{
		this->addChild(m_Drops.back(), 11);
		m_Drops.back()->setTag(Coin_TAG);

		m_Drops.back()->getSprite()->setOpacity(0);
		m_Drops.back()->bindPlayer(m_scene->getPlayer());
		m_Drops.back()->bindMap(this);
	}


}
void BattleMap::DropsUpdate(float dt)
{
	for (int i = 0; i < m_Drops.size(); i++)
	{
		if (m_monster.at(i)->getIsDead()&&m_Drops.at(i)->getIsCanSee()==0&& m_Drops.at(i)->getIsUsed()==0)
		{
			//掉落物
			m_Drops.at(i)->getSprite()->setOpacity(255);
			m_Drops.at(i)->setPosition(m_monster.at(i)->getPosition());
		}
	}
	for (int i = 0; i < m_Drops.size(); i++)
	{
		if (m_Drops.at(i)->isAround(30)&& m_Drops.at(i)->getIsCanSee()==0&& m_Drops.at(i)->getIsUsed()==0)
		{
			m_Drops.at(i)->Interact(0);
			m_Drops.at(i)->getSprite()->setOpacity(0);
		}
	}
}
std::vector<Item*> BattleMap::getDrops()
{
	return m_Drops;
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


