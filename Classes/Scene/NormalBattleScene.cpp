#include"NormalBattleScene.h"
#include"Player.h";
#include"music/music.h"
#include"PlayerMove.h"
#include"TreasureBoxes.h"
#include"AllTag.h"
#include"Weapon.h"
#include"BossInterlude.h"
USING_NS_CC;
MusicManager* NormalBattleScene::getmusicManager()
{
	return m_musicManager;
}

void NormalBattleScene::bindPlayer(Player* player)
{
	m_player = player;
}

Player* NormalBattleScene::getPlayer()
{
	return m_player;
}

BattleMap* NormalBattleScene::getParentMap()
{
	return parentMap;
}

void NormalBattleScene::changeMap(int x)
{
	static int i = 1;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto temp = parentMap->getPosition();
	auto test = m_battleMap.at(x)->getPosition();
	parentMap->setPosition(m_battleMap.at(x)->getPosition());
	removeChild(parentMap);
	parentMap = m_battleMap.at(x);
	parentMap->setPosition(temp);
	m_player->getplayermove()->bindMap(m_battleMap.at(x)->getBattleMap());
	if (parentMap->getTag()!=2)
	{
		if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
			parentMap->createMonster(4);
		else if (parentMap->getBattleMap()->getTag() == BossRoom_TAG)
			parentMap->createMonster(0);
		else if (parentMap->getBattleMap()->getTag() == HiddenRoom_TAG)
			parentMap->createMonster(4);
		//给每个怪物增加刚体
		for (int i = 0; i < parentMap->getMonster().size(); i++)
		{
			float x = parentMap->getMonster().at(i)->Width;
			float y = parentMap->getMonster().at(i)->Height;

			auto physicsBody_M_1 = PhysicsBody::createBox(Size(x,y),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody_M_1->setDynamic(false);

			parentMap->getMonster().at(i)->addComponent(physicsBody_M_1);
			parentMap->getMonster().at(i)->getPhysicsBody()->setPositionOffset(Vec2(x/2,y/2));
			physicsBody_M_1->setCategoryBitmask(0x0001);//0011
			physicsBody_M_1->setCollisionBitmask(0x0001);//0001
			physicsBody_M_1->setContactTestBitmask(0x0001);
			parentMap->getMonster().at(i)->setPhysicsBody(physicsBody_M_1);

			//Boss怪，额外增加一个永久跟随的隐形子弹当作碰撞伤害
			if (parentMap->getMonster().at(i)->getTag() == CthulhuEye_Monster_TAG)
			{
				parentMap->getMonster().at(i)->ImmortalAmmo = parentMap->getMonster().at(i)->MonsterAttack();
				auto physicBody = PhysicsBody::createBox(Size(parentMap->getMonster().at(i)->getSprite()->getContentSize()),
					PhysicsMaterial(0, 0, 0));//添加刚体
				parentMap->getMonster().at(i)->ImmortalAmmo->addComponent(physicBody);
				parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setDynamic(false);
				parentMap->getMonster().at(i)->ImmortalAmmo->getSprite()->setOpacity(0);

				parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setCategoryBitmask(0x0010);//掩码，怪物子弹和玩家相同
				parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setCollisionBitmask(0x0010);
				parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setContactTestBitmask(0x0010);

				parentMap->getMonster().at(i)->addChild(parentMap->getMonster().at(i)->ImmortalAmmo, -1);
				parentMap->getMonster().at(i)->ImmortalAmmo->setTag(MonsterAmmo_ImmortalTAG);

			}


		}
		//宝箱创建,血瓶创建
		if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
		{
			parentMap->BoxInit();
			parentMap->getBox().back()->bindScene(this);
			parentMap->BoxCreate();
			int i = rand() % 3 + 1;
			parentMap->getBox().back()->BoxBirth(i);

			parentMap->ItemInit();//宝箱里的血瓶创建
			parentMap->getItems().back()->bindScene(this);
			parentMap->ItemCreate();



			parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
		}
		else if (parentMap->getBattleMap()->getTag() == BossRoom_TAG|| parentMap->getBattleMap()->getTag() == ShopRoom_TAG)
		{
			for (int i = 1; i <= 3; i++)
			{
				parentMap->BoxInit();
				parentMap->getBox().back()->bindScene(this);
				parentMap->BoxCreate();
				parentMap->getBox().back()->BoxBirth(i);

				parentMap->ItemInit();//宝箱里的物品创建
				parentMap->getItems().back()->bindScene(this);
				parentMap->ItemCreate();

			}
			parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);


		}
		//打怪掉钱
		if (parentMap->getBattleMap()->getTag() != BossRoom_TAG)
		{
			parentMap->DropsInit();
			for (int i = 0; i < parentMap->getDrops().size(); i++)
			{
				parentMap->getDrops().at(i)->bindScene(this);
			}
			parentMap->DropsCreate(0);
		}
	
		//陷阱创建
		if (parentMap->getBattleMap()->getTag() != ShopRoom_TAG
			&& parentMap->getBattleMap()->getTag() != BossRoom_TAG)
		{
			int TrapsNum = rand() % 5 + 1;
			for (int i = 1; i <= TrapsNum; i++)
			{
				parentMap->TrapsInit();
				parentMap->getTraps().back()->bindScene(this);
				parentMap->getTraps().back()->setScale(1.5);
				parentMap->TrapsCreate(i);
				parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::TrapsUpdate), 0.1f);
			}
		}
		
	//	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::TrapsUpdate), 0.1f);

		//祈祷雕像创建
		if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
		{
			
			if (rand() % 2)
			{
				parentMap->StatueInit();
				parentMap->getStatue().back()->bindScene(this);
				parentMap->StatueCreate();
				parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::StatueUpdate), 0.1f);

			}
				
			


		}
		else if (parentMap->getBattleMap()->getTag() == ShopRoom_TAG)
		{
			parentMap->StatueInit();
			parentMap->getStatue().back()->bindScene(this);
			parentMap->StatueCreate();
			parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::StatueUpdate), 0.1f);
		}

		

	}
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::StatueUpdate), 0.1f);
	if (parentMap->getBattleMap()->getTag() == ShopRoom_TAG||
		parentMap->getBattleMap()->getTag()==BossRoom_TAG)
	{
		parentMap->getWeapon()->bindPlayer(getPlayer());
	}

	//Update must be opened
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::DropsUpdate), 0.1f);


	addChild(parentMap, 1);
	
	if (parentMap->getBattleMap()->getTag() == BossRoom_TAG && parentMap->getTag()!=2)//进Boss房
	{
		auto bossInterlude = BossInterlude::create();
		bossInterlude->playInterlude(getPlayer(), parentMap->getMonster().back());
		MusicManager::changeMusic("bgm/boss1.mp3");

		Director::getInstance()->pushScene(TransitionTurnOffTiles::create(1.2f, bossInterlude));
		
	}
	parentMap->setTag(2);//表示已经到过该地图
}
void NormalBattleScene::Mapinit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	switch (rand() % 4)
	{
	case 0:
		start_num = 0;
		boss_num = 15;
		//*shop_num = rand() % 2 ? 2 : 6;
		break;
	case 1:
		start_num = 15;
		boss_num = 0;
		//*shop_num = rand() % 2 ? 0 : 8;
		break;
	case 2:
		start_num = 3;
		boss_num = 12;
		//*shop_num = rand() % 2 ? 0 : 8;
		break;
	case 3:
		start_num = 12;
		boss_num = 3;
		//*shop_num = rand() % 2 ? 2 : 6;
		break;
	default:
		break;
	};
	for (int i = 0; i < 16; i++)//默认开始全能通过
	{
		virtualMap[i] = 1;
	}
	for (int i = 0; i < 6;i++)//生成6个障碍物,即一共能实际通过的地图有十张
	{
		int x = rand() % 16;
		if (virtualMap[x]==1 && x!=start_num)
		{
			virtualMap[x] = 0;
		}
		else
		{
			i--;
			continue;
		}
		if (isConnected(i))
		{
			continue;
		}
		else
		{
			i--;
			virtualMap[x] = 1;
			continue;
		}

	}
	do
	{
		shop_num = rand() % 16;
	} while (virtualMap[shop_num] != 1 || shop_num == boss_num || shop_num == start_num);
	//boss_num = start_num;

	while (1)
	{
		hid_num = rand() % 16;
		if (!virtualMap[hid_num])
		{
			virtualMap[hid_num] = true;
			break;
		}

	}
	for (int i = 0; i < 16; i++)//取10张地图
	{
		if (virtualMap[i]==1)
		{
			m_battleMap.pushBack(BattleMap::create());
			m_battleMap.back()->bindScene(this);
			if (i == shop_num)
				m_battleMap.back()->MapInit(1);//MapInit可传参，0为普通战斗图，1为商店图
			else if (i==boss_num)		
				m_battleMap.back()->MapInit(2);			
			else if(i==hid_num)
				m_battleMap.back()->MapInit(4);
			else 
				m_battleMap.back()->MapInit(0);
			m_battleMap.back()->setPosition(visibleSize.width * (i % 3), visibleSize.width * (i / 3));
			m_battleMap.back()->setNumber(i);
			m_battleMap.back()->setName("ok");
		}
		else
		{
			m_battleMap.pushBack(BattleMap::create());
			m_battleMap.back()->setName("no");
		}
		
	}

	parentMap = m_battleMap.at(start_num);//初始地图取左下角0号
	auto temp = parentMap->getPosition();
	parentMap->setPosition(m_battleMap.at(0)->getPosition());
	m_battleMap.at(0)->setPosition(temp);


	if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
		parentMap->createMonster(4);
	else if (parentMap->getBattleMap()->getTag() == BossRoom_TAG)
		parentMap->createMonster(0);
	else if(parentMap->getBattleMap()->getTag() == HiddenRoom_TAG)
		parentMap->createMonster(4);
	addChild(parentMap, 1);

	parentMap->setTag(2);
	for (int i = 0; i < parentMap->getMonster().size(); i++)//给初始地图的怪物添加刚体
	{
		float x = parentMap->getMonster().at(i)->Width;
		float y = parentMap->getMonster().at(i)->Height;
		auto physicsBody_M = PhysicsBody::createBox(Size(x, y),
			PhysicsMaterial(0.0f, 0.0f, 0.0f));
		parentMap->getMonster().at(i)->addComponent(physicsBody_M);
		parentMap->getMonster().at(i)->getPhysicsBody()->setPositionOffset(Vec2(x / 2, y / 2));
		physicsBody_M->setDynamic(false);
		physicsBody_M->setCategoryBitmask(0x0001);//0011掩码
		physicsBody_M->setCollisionBitmask(0x0001);//0001
		physicsBody_M->setContactTestBitmask(0x0001);
		parentMap->getMonster().at(i)->setPhysicsBody(physicsBody_M);

		if (parentMap->getMonster().at(i)->getTag() == CthulhuEye_Monster_TAG)//Boss怪，额外增加一个永久跟随的子弹当作碰撞伤害
		{
			parentMap->getMonster().at(i)->ImmortalAmmo = parentMap->getMonster().at(i)->MonsterAttack();
			auto physicBody = PhysicsBody::createBox(Size(parentMap->getMonster().at(i)->getSprite()->getContentSize()),
				PhysicsMaterial(0, 0, 0));//添加刚体
			parentMap->getMonster().at(i)->ImmortalAmmo->addComponent(physicBody);
			parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setDynamic(false);
			parentMap->getMonster().at(i)->ImmortalAmmo->getSprite()->setOpacity(0);

			parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setCategoryBitmask(0x0010);//掩码，怪物子弹和玩家相同
			parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setCollisionBitmask(0x0010);
			parentMap->getMonster().at(i)->ImmortalAmmo->getPhysicsBody()->setContactTestBitmask(0x0010);

			parentMap->getMonster().at(i)->addChild(parentMap->getMonster().at(i)->ImmortalAmmo,-1);
			parentMap->getMonster().at(i)->ImmortalAmmo->setTag(MonsterAmmo_ImmortalTAG);

		}

	}


}
bool NormalBattleScene::isConnected(int obstacle)//看地图是否联通
{
	bool isvisited[16] = { 0 };
	std::queue<int> MapQueue;
	std::vector<int> MapCanReach;
	MapQueue.push(start_num);
	isvisited[start_num] = 1;
	while (MapQueue.size()>0)
	{
		int i = MapQueue.front();
		MapCanReach.push_back(i);
		MapQueue.pop();
		if ((i + 1) <= 15 && (i + 1) % 4 != 0 && virtualMap[i + 1] == 1 && isvisited[i + 1] != 1)
		{
			MapQueue.push(i + 1);
			isvisited[i+1] = 1;
		}
		if ((i - 1) >= 0 && (i - 1) % 4 != 3 && virtualMap[i - 1] == 1 && isvisited[i - 1] != 1)
		{
			MapQueue.push(i - 1);
			isvisited[i-1] = 1;
		}
		if ((i - 4) >= 0 &&virtualMap[i - 4] == 1 && isvisited[i - 4] != 1)
		{
			MapQueue.push(i - 4);
			isvisited[i-4] = 1;
		}
		if ((i + 4) <= 15 && virtualMap[i + 4] == 1 && isvisited[i + 4] != 1)
		{
			MapQueue.push(i + 4);
			isvisited[i+4] = 1;
		}
	}
	bool canReachBoss = 0;//能否到达BOSS房
	for (auto x : MapCanReach)
	{
		if (x==boss_num)
		{
			canReachBoss = 1;
		}
	}
	if (!canReachBoss)
	{
		return 0;
	}
	else
	{
		if (MapCanReach.size() >= 10)
			return 1;
	}
}
int NormalBattleScene::getStartRoom()
{
	return start_num;
}
int NormalBattleScene::getBossRoom()
{
	return boss_num;
}
int NormalBattleScene::getShopRoom()
{
	return shop_num;
}

int NormalBattleScene::getHidRoom()
{
	return hid_num;
}

void NormalBattleScene::bindWeaponManager(WeaponManager* WeaponManager)
{
	m_weaponManager = WeaponManager;
}

WeaponManager* NormalBattleScene::getWeaponManager()
{
	return m_weaponManager;
}
Vector<MapGate*> NormalBattleScene::getMapGate()
{
	return m_mapgate;
}

Vector<BattleMap*> NormalBattleScene::getBattleMap()
{
	return m_battleMap;
}

int NormalBattleScene::getBattleLevel()
{
	return level;
}

int NormalBattleScene::level;