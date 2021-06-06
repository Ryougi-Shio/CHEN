#include"NormalBattleScene.h"
#include"Player.h";
#include"music/music.h"
#include"PlayerMove.h"
#include"TreasureBoxes.h"
USING_NS_CC;
void NormalBattleScene::bindWeaponManager(WeaponManager* WeaponManager)
{
	m_weaponManager = WeaponManager;
}

WeaponManager* NormalBattleScene::getWeaponManager()
{
	return m_weaponManager;
}

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
		parentMap->BoxInit();
		parentMap->getBox()->setTag(TreasureBox_TAG);
		parentMap->getBox()->bindScene(this);
		parentMap->getBox()->bindMap(parentMap);
		parentMap->getBox()->bindPlayer(getPlayer());
		parentMap->addChild(parentMap->getBox(), 1);
		parentMap->getBox()->setPosition(visibleSize / 2);
	}
	parentMap->setTag(2);//表示已经到过该地图
	addChild(parentMap, 1);
	//parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::MonsterUpdate), 0.01f);
	
}
