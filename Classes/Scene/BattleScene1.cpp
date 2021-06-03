#include"BattleScene1.h"
#include"music/music.h"
#include"Map/BattleMap.h"
#include"Player.h"
#include"PlayerMove.h"
#include"PlayerAttribute.h"
#include"Pistol.h"
#include"PistolAmmo.h"
#include"Monster.h"

static long SwordEnd;
bool BattleScene1::init()
{
	srand((unsigned)time(NULL));//根据时间取随机种子
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	if (initWithPhysics()) {
		getPhysicsWorld()->setGravity(Vec2::ZERO);
		getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		getPhysicsWorld()->setSubsteps(20);
	}
	getmusicManager()->changeMusic("bgm/Room.mp3");
	for (int i = 0; i <9; i++)//取九张地图
	{
		m_battleMap.pushBack(BattleMap::create());
		m_battleMap.back()->bindScene(this);
		m_battleMap.back()->setPosition(visibleSize.width * (i % 3), visibleSize.width * (i / 3));
		m_battleMap.back()->setNumber(i);
	}
	parentMap = m_battleMap.at(0);
	addChild(m_battleMap.at(0),1);
	m_battleMap.at(0)->createMonster();
	m_battleMap.at(0)->setTag(2);
	auto physicsBody_M_1 = PhysicsBody::createBox(Size(46.0f, 48.0f),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	parentMap->getMonster().back()->addComponent(physicsBody_M_1);
	physicsBody_M_1->setDynamic(false);
	physicsBody_M_1->setCategoryBitmask(0x0001);//0011
	physicsBody_M_1->setCollisionBitmask(0x0001);//0001
	physicsBody_M_1->setContactTestBitmask(0x0001);

	//设置按钮
	auto settings = MenuItemImage::create("ui/settings.png", "ui/settings.png", [&](Ref* sender) {
		getmusicManager()->effectPlay("effect/button.mp3");
		getmusicManager()->menu(this);
	});
	//位置位于左上角
	settings->setPosition(visibleSize.width - settings->getContentSize().width / 2, visibleSize.height - settings->getContentSize().height / 2);
	//菜单
	auto menu = Menu::create(settings, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 3);

	//玩家创建
	auto physicsBody = PhysicsBody::createBox(Size(40.0f, 40.0f),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	bindPlayer(Player::create());
	getPlayer()->setTag(MyTag::Player_TAG);
	getPlayer()->addComponent(physicsBody);
	getPlayer()->getPhysicsBody()->setCategoryBitmask(0x0010);
	getPlayer()->getPhysicsBody()->setCollisionBitmask(0x0010);
	getPlayer()->getPhysicsBody()->setContactTestBitmask(0x0010);
	getPlayer()->setPosition(64 * 4 + 32, 64 * 4 + 32);
	getPlayer()->getplayermove()->bindMap(parentMap->getBattleMap());//PlayerMove跟这个地图绑定
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//属性UI位置设置
	this->addChild(getPlayer()->getPlayerAttribute(), 4);
	this->addChild(getPlayer(), 2);
	//MapGate测试
	
	////eventlistener,键盘监听，用于移动人物
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘按下时响应
	{
		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove里keyMap的对应键码置true
		if (keycode==EventKeyboard::KeyCode::KEY_E)
		{
			inGate();
		}
	};

	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘松开时响应
	{
		getPlayer()->getplayermove()->FalseKeyCode(keycode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	//鼠标监听
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseMove = [=](cocos2d::Event* event)//移动
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->changeMouseLocation(e->getLocation());


	};
	myMouseListener->onMouseDown = [=](cocos2d::Event* event)//按下
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->trueMouseMap(e->getMouseButton());

	};
	myMouseListener->onMouseUp = [=](cocos2d::Event* event)//松开
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->flaseMouseMap(e->getMouseButton());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene1::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
//	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::test), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::DeleteAmmo), 0.001f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::Ammoupdate), 0.01f);//每0.01s检测玩家子弹是否需要生成	
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::AmmoUpdate_Monster), 0.3f);//怪物子弹
	MapGateInit();
	return 1;
}
void BattleScene1::MapGateInit()
{
	for (int i = 1; i <= 4; i++)
	{
		m_mapgate.pushBack(MapGate::create());
		m_mapgate.back()->bindPlayer(getPlayer());
		this->addChild(m_mapgate.back(), 5);
		m_mapgate.back()->IsAble(false);
	}
	//下
	m_mapgate.at(1)->setPosition(Director::getInstance()->getVisibleSize().width / 2, m_mapgate.back()->getSprite()->getContentSize().height * 0.5 + 64);
	//上
	m_mapgate.at(0)->setPosition(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height- m_mapgate.back()->getSprite()->getContentSize().height * 0.5 - 64);
	//左
	m_mapgate.at(2)->setPosition(m_mapgate.back()->getSprite()->getContentSize().width/2+64, Director::getInstance()->getVisibleSize().height / 2);
	//右
	m_mapgate.at(3)->setPosition(Director::getInstance()->getVisibleSize().width- m_mapgate.back()->getSprite()->getContentSize().width / 2-64,
		Director::getInstance()->getVisibleSize().height / 2);
}
void BattleScene1::inGate()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_mapgate.at(i)->getAble())
		{
			if (m_mapgate.at(i)->isAround(getPlayer()->getPositionX(), getPlayer()->getPositionY()) )
			{
				CCLOG("%d", parentMap->getNumber());
				switch (i)
				{
				case 0:
					changeMap(parentMap->getNumber() + 3);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width / 2, m_mapgate.back()->getSprite()->getContentSize().height * 0.5 + 64);
					break;
				case 1:
					changeMap(parentMap->getNumber() - 3);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width / 2,
						Director::getInstance()->getVisibleSize().height - m_mapgate.back()->getSprite()->getContentSize().height * 0.5 - 64);
					break;
				case 2:
					changeMap(parentMap->getNumber() - 1);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width - m_mapgate.back()->getSprite()->getContentSize().width / 2 - 64,
						Director::getInstance()->getVisibleSize().height / 2);
					break;
				case 3:
					changeMap(parentMap->getNumber() + 1);
					getPlayer()->setPosition(m_mapgate.back()->getSprite()->getContentSize().width / 2 + 64,
						Director::getInstance()->getVisibleSize().height / 2);
					break;
				default:
					break;
				}
				break;
			}
			
		}
	}
}
void BattleScene1::update(float dt)
{
	int able = 1;
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		if (parentMap->getMonster().at(i)->getIsDead()==0)
			able = 0;
	}
	int x = parentMap->getNumber()%3+1;
	int y = parentMap->getNumber() / 3+1;
	for (int i = 0; i < 4; i++)
	{
		m_mapgate.at(i)->IsAble(0);
	}
	if (x <= 2)
	{
		m_mapgate.at(3)->IsAble(able);
	}
	if (x >= 2)
	{
		m_mapgate.at(2)->IsAble(able);
	}
	if (y >= 2)
	{
		m_mapgate.at(1)->IsAble(able);
	}
	if (y <= 2)
	{
		m_mapgate.at(0)->IsAble(able);
	}
}
void BattleScene1::AmmoUpdate_Monster(float dt)
{
	//怪物Pistol子弹
	float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
	float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		bool CanShoot = 0;
		float Mx = parentMap->getMonster().at(i)->getPositionX();
		float My = parentMap->getMonster().at(i)->getPositionY();
		Vec2 m = Vec2(Vec2(Px - Mx, Py - My) / sqrt((Px - Mx) * (Px - Mx) + (Py - My) * (Py - My)));

		if (parentMap->getMonster().at(i)->getIsDead() == 0 && parentMap->getMonster().at(i)->isAround())//没死
		{

			m_monsterPistolAmmoList.push_back(parentMap->getMonster().at(i)->MonsterAttack());
			m_monsterPistolAmmoList.back()->start = clock();
			m_monsterPistolAmmoList.back()->setTag(MyTag::MonsterAmmo_TAG);
			addChild(m_monsterPistolAmmoList.back(), 3);
			auto physicBody = PhysicsBody::createBox(Size(10.0f, 10.0f), PhysicsMaterial(0, 0, 0));
			m_monsterPistolAmmoList.back()->addComponent(physicBody);
			m_monsterPistolAmmoList.back()->getPhysicsBody()->setDynamic(false);
			m_monsterPistolAmmoList.back()->setPosition(parentMap->getMonster().at(i)->getPosition());
			m_monsterPistolAmmoList.back()->getPhysicsBody()->setVelocity(m * 500);

			m_monsterPistolAmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0010);//怪物子弹和玩家同
			m_monsterPistolAmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0010);
			m_monsterPistolAmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0010);
		}
	}
}
void BattleScene1::Ammoupdate(float dt)//玩家子弹的生成
{

	float x = getPlayer()->getMouseLocation().x;
	float y = Director::getInstance()->getVisibleSize().height - getPlayer()->getMouseLocation().y;
	float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
	float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
	float Wx = (Px + getPlayer()->getWeapon1()->getPositionX() + getPlayer()->getWeapon1()->getContentSize().width / 2);
	float Wy = (Py + getPlayer()->getWeapon1()->getPositionY());
	Vec2 v = Vec2(Vec2(x - Wx, y - Wy) / sqrt((x - Wx) * (x - Wx) + (y - Wy) * (y - Wy)));//从人物指向鼠标位置的单位向量

	//玩家Pistol子弹
	if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT]&&getPlayer()->getPlayerAttribute()->getHp()>0&&getPlayer()->getWeapon1()->getTag()==0)
	{
		bool CanShoot = 0;
		if (AmmoList.size() == 0)//第一发子弹允许射出
			CanShoot = 1;
		else if (clock() - AmmoList.back()->start > 300)//两子弹之间时间间隔大于0.3s才允许射出
			CanShoot = 1;
		if (CanShoot)
		{
			AmmoList.push_back(getPlayer()->getWeapon1()->Attack());
			AmmoList.back()->setTag(MyTag::PlayerAmmo_TAG);
			AmmoList.back()->start = clock();//每个子弹内部的start负责记录出生时刻
			addChild(AmmoList.back(), 3);
			auto physicBody = PhysicsBody::createBox(Size(10.0f, 10.0f), PhysicsMaterial(0, 0, 0));
			AmmoList.back()->addComponent(physicBody);
			AmmoList.back()->getPhysicsBody()->setDynamic(false);
			AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
			AmmoList.back()->getPhysicsBody()->setVelocity(v * 500);
			AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
			AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
			AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
		}
	
	}
	//玩家Sword子弹
	if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT] && getPlayer()->getPlayerAttribute()->getHp() > 0 && getPlayer()->getWeapon1()->getTag() == 1)
	{
		bool CanShoot = 0;


		if (AmmoList.size() == 0)
		{
			if (clock() - SwordEnd > 300)
			{
				CCLOG("S:%ld,Clock:%ld",SwordEnd,clock());
				CanShoot = 1;
			}

		}
		else if (clock() - AmmoList.back()->start > 300)
			CanShoot = 1;
		if (CanShoot)
		{

			AmmoList.push_back(getPlayer()->getWeapon1()->Attack());
			AmmoList.back()->start = clock();
			AmmoList.back()->setTag(MyTag::PlayerAmmo_Sword_TAG);
			addChild(AmmoList.back(), 3);
			auto physicBody = PhysicsBody::createBox(Size(60.0f, 60.0f), PhysicsMaterial(0, 0, 0));
			AmmoList.back()->addComponent(physicBody);
			AmmoList.back()->getPhysicsBody()->setDynamic(false);
			AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
			AmmoList.back()->getPhysicsBody()->setVelocity(v * 1500);
			AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
			AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
			AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
			if (getPlayer()->getIsFlip())
				AmmoList.back()->getSprite()->setFlippedX(1);
		}
		if (AmmoList.size())
			getPlayer()->getWeapon1()->getSprite()->setOpacity(0);
		else
			getPlayer()->getWeapon1()->getSprite()->setOpacity(255);
	}
	
}

bool BattleScene1::isWall(float x, float y)
{
	int mapX = (int)(x / 64);
	int mapY = (int)(12 - y / 64);
	int tileGid = parentMap->getBattleMap()->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
	if (tileGid)
		return true;	//是墙

	else
		return false;	//不是墙
}

void BattleScene1::DeleteAmmo(float dt)
{
	if (AmmoList.size() != 0)
	{
		int i = 0;
		auto ix = AmmoList.begin();
		int size = AmmoList.size();

		if (getPlayer()->getWeapon1()->getTag() == Weapon::MyWeapon::Sword_Player)//Sword的子弹回收
		{

			
			for (; i < size; ix++, i++)
			{
				AmmoList[i]->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
				double NowTime = clock();

				if (NowTime - AmmoList[i]->start -300>= -10 )
				{
					removeChild(AmmoList[i]);
					AmmoList.erase(ix);
					SwordEnd = clock();
					break;
				}
			}
		}
		else
		{	//Pistol的子弹撞墙回收
			for (; i < size; ix++, i++)
			{
				if (isWall((*ix)->getPositionX(), (*ix)->getPositionY()))
				{
					removeChild(AmmoList[i]);
					AmmoList.erase(ix);
					break;
				}

			}
		}

	}
	//怪物手枪子弹的撞墙回收 
	if (m_monsterPistolAmmoList.size() != 0)
	{
		int i = 0;
		auto ix = m_monsterPistolAmmoList.begin();
		int size = m_monsterPistolAmmoList.size();
		for (; i < size; ix++, i++)
		{
			if (isWall((*ix)->getPositionX(), (*ix)->getPositionY()))
			{
				removeChild(m_monsterPistolAmmoList[i]);
				m_monsterPistolAmmoList.erase(ix);
				break;
			}

		}
	}

}
//碰撞检测
bool BattleScene1::onContactBegin(PhysicsContact& contact)
{
	Ammo* ammo;
	MonsterPistolAmmo* ammo_M;
	Monster* monster;
	Player* player;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	int TagA = nodeA->getTag();
	int TagB = nodeB->getTag();
	if (TagA == MyTag::PlayerAmmo_TAG|| TagA == MyTag::PlayerAmmo_Sword_TAG)
		ammo = dynamic_cast<Ammo*>(nodeA);
	else if (TagA == MyTag::Monster_TAG)
		monster = dynamic_cast<Monster*>(nodeA);
	else if (TagA == 0)
		player = dynamic_cast<Player*>(nodeA);
	else if (TagA == MyTag::MonsterAmmo_TAG)
		ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeA);

	if (TagB== MyTag::PlayerAmmo_TAG || TagB == MyTag::PlayerAmmo_Sword_TAG)
		ammo = dynamic_cast<Ammo*>(nodeB);
	else if (TagB == MyTag::Monster_TAG)
		monster = dynamic_cast<Monster*>(nodeB);
	else if (TagB == 0)
		player = dynamic_cast<Player*>(nodeB);
	else if (TagB == MyTag::MonsterAmmo_TAG)
		ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeB);
	//怪物撞玩家手枪子弹
	if ((TagB==MyTag::Monster_TAG&&TagA==MyTag::PlayerAmmo_TAG)|| (TagA == MyTag::Monster_TAG && TagB == MyTag::PlayerAmmo_TAG))
	{
		int i = 0;
		auto ix = AmmoList.begin();
		int size = AmmoList.size();
		for (; i < size; ix++, i++)
		{
			if (*ix == ammo)
			{
				removeChild(AmmoList[i]);
				AmmoList.erase(ix);
				break;
			}
		}
		monster->takingDamage(1);
	}
	//怪物撞玩家刀剑子弹
	if ((TagB == MyTag::Monster_TAG && TagA == MyTag::PlayerAmmo_Sword_TAG) || (TagA == MyTag::Monster_TAG && TagB == MyTag::PlayerAmmo_Sword_TAG))
	{
		int i = 0;
		auto ix = AmmoList.begin();
		int size = AmmoList.size();
		for (; i < size; ix++, i++)
		{
			if (*ix == ammo)
			{
				removeChild(AmmoList[i]);
				AmmoList.erase(ix);
				SwordEnd = clock();
				break;
			}
		}
		monster->takingDamage(1);
	}
	//玩家撞怪物子弹
	if ((TagA==MyTag::Player_TAG&&TagB==MyTag::MonsterAmmo_TAG)|| (TagB == MyTag::Player_TAG && TagA == MyTag::MonsterAmmo_TAG))
	{
		int i = 0;
		auto ix = m_monsterPistolAmmoList.begin();
		int size = m_monsterPistolAmmoList.size();
		for (; i < size; ix++, i++)
		{
			if (*ix == ammo_M)
			{
				removeChild(m_monsterPistolAmmoList[i]);
				m_monsterPistolAmmoList.erase(ix);
				break;
			}
		}
		getPlayer()->getPlayerAttribute()->takeDamage(1);
	}
	return 1;
}
