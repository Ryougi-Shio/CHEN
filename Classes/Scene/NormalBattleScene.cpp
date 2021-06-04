#include"NormalBattleScene.h"
#include"Player.h";
#include"music/music.h"
#include"PlayerMove.h"
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
		parentMap->createMonster(4);

		for (int i = 0; i < parentMap->getMonster().size(); i++)
		{
			auto physicsBody_M_1 = PhysicsBody::createBox(Size(46.0f, 48.0f),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody_M_1->setDynamic(false);

			parentMap->getMonster().at(i)->addComponent(physicsBody_M_1);
			physicsBody_M_1->setCategoryBitmask(0x0001);//0011
			physicsBody_M_1->setCollisionBitmask(0x0001);//0001
			physicsBody_M_1->setContactTestBitmask(0x0001);
			parentMap->getMonster().at(i)->setPhysicsBody(physicsBody_M_1);
		}

	}
	parentMap->setTag(2);//表示已经到过该地图
	addChild(parentMap, 1);
	//parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::MonsterUpdate), 0.01f);
	
}
