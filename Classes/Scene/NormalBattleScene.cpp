#include"NormalBattleScene.h"
#include"Player.h";
#include"music/music.h"
#include"PlayerMove.h"
#include"TreasureBoxes.h"
#include"AllTag.h"
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
		}
		//宝箱创建,血瓶创建
		if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
		{
			parentMap->BoxInit();
			parentMap->getBox().back()->bindScene(this);
			parentMap->BoxCreate();
			parentMap->getBox().back()->BoxBirth(1);

			parentMap->ItemInit();//宝箱里的血瓶创建
			parentMap->getItems().back()->bindScene(this);
			parentMap->ItemCreate();



			parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
		}
	
		//打怪掉钱
		parentMap->DropsInit();
		for (int i = 0; i < parentMap->getDrops().size(); i++)
		{
			parentMap->getDrops().at(i)->bindScene(this);

		}
		parentMap->DropsCreate();
	}
	//Update must be opened
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::DropsUpdate), 0.1f);


	parentMap->setTag(2);//表示已经到过该地图
	addChild(parentMap, 1);
	//parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::MonsterUpdate), 0.01f);
	
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
	for (int i = 0; i < 6;i++)//生成六个障碍物,即一共能实际通过的地图有十张
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
	for (int i = 0; i < 16; i++)//取九张地图
	{
		if (virtualMap[i]==1)
		{
			m_battleMap.pushBack(BattleMap::create());
			m_battleMap.back()->bindScene(this);
			if (i == shop_num)
				m_battleMap.back()->MapInit(1);//MapInit可传参，0为普通战斗图，1为商店图
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
		parentMap->createMonster(4);//创建4只随机怪物
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
