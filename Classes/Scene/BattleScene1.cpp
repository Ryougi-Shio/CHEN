#include"BattleScene1.h"
#include"music/music.h"
#include"Map/BattleMap.h"
#include"Player.h"
#include"PlayerMove.h"
#include"PlayerAttribute.h"
#include"Pistol.h"
#include"PistolAmmo.h"
#include"Monster.h"
bool BattleScene1::init()
{
	srand((unsigned)time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	if (initWithPhysics()) {
		getPhysicsWorld()->setGravity(Vec2::ZERO);
		getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		getPhysicsWorld()->setSubsteps(20);
	}

	getmusicManager()->changeMusic("bgm/Room.mp3");
	for (int i = 0; i < 9; i++)
	{
		m_battleMap.pushBack(BattleMap::create());
		m_battleMap.back()->bindScene(this);
		m_battleMap.back()->setPosition(visibleSize.width * (i % 3), visibleSize.width * (i / 3));
	}

	parentMap = m_battleMap.at(0);
	addChild(m_battleMap.at(0),1);
	m_battleMap.at(0)->createMonster();
	m_battleMap.at(0)->setTag(MyTag::Monster_TAG);
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

	////eventlistener,键盘监听，用于移动人物
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘按下时响应
	{
		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove里keyMap的对应键码置true

	};

	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘松开时响应
	{
		getPlayer()->getplayermove()->FalseKeyCode(keycode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	//鼠标
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseMove = [=](cocos2d::Event* event)
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->changeMouseLocation(e->getLocation());


	};
	myMouseListener->onMouseDown = [=](cocos2d::Event* event)
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->trueMouseMap(e->getMouseButton());

	};
	myMouseListener->onMouseUp = [=](cocos2d::Event* event)
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
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::Ammoupdate), getPlayer()->getWeapon1()->getShootSpeed());
	
	return 1;
}

void BattleScene1::update(float dt)
{

	if (getPlayer()->getplayermove()->getkeyMap()[EventKeyboard::KeyCode::KEY_Q])
	{
		changeMap(rand() % 9);
	}
}

void BattleScene1::Ammoupdate(float dt)
{
	int dd=parentMap->getMonster().at(0)->getIsDead();
	CCLOG("%d", dd);
	



	float x = getPlayer()->getMouseLocation().x;
	float y = Director::getInstance()->getVisibleSize().height - getPlayer()->getMouseLocation().y;
	float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
	float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
	float Wx = (Px + getPlayer()->getWeapon1()->getPositionX() + getPlayer()->getWeapon1()->getContentSize().width / 2);
	float Wy = (Py + getPlayer()->getWeapon1()->getPositionY());
	Vec2 v = Vec2(Vec2(x - Wx, y - Wy) / sqrt((x - Wx) * (x - Wx) + (y - Wy) * (y - Wy)));
	//CCLOG("%f %f", Px, Py);
	if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT]&&getPlayer()->getPlayerAttribute()->getHp()>0)
	{
		AmmoList.push_back(getPlayer()->getWeapon1()->Attack());
		AmmoList.back()->setTag(MyTag::PlayerAmmo_TAG);
		addChild(AmmoList.back(),3);
		auto physicBody = PhysicsBody::createBox(Size(10.0f, 10.0f), PhysicsMaterial(0, 0, 0));
		AmmoList.back()->addComponent(physicBody);
		//AmmoList.back()->getPhysicsBody()->setDynamic(false);
		AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
		AmmoList.back()->getPhysicsBody()->setVelocity(v * 500);
		AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
		AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
		AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
	}
	//怪物子弹
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		CCLOG("%d", i);
		float Mx = parentMap->getMonster().at(i)->getPositionX();
		float My = parentMap->getMonster().at(i)->getPositionY();
		Vec2 m = Vec2(Vec2(Px -Mx, Py - My) / sqrt((Px - Mx) * (Px - Mx) + (Py - My)*(Py - My)));
		if (parentMap->getMonster().at(i)->getIsDead() == 0&&parentMap->getMonster().at(i)->isAround())//没死
		{

			m_monsterPistolAmmoList.push_back(parentMap->getMonster().at(i)->MonsterAttack());
			m_monsterPistolAmmoList.back()->setTag(MyTag::MonsterAmmo_TAG);
			addChild(m_monsterPistolAmmoList.back(),3);
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

bool BattleScene1::onContactBegin(PhysicsContact& contact)
{
	PistolAmmo* ammo;
	MonsterPistolAmmo* ammo_M;
	Monster* monster;
	Player* player;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	int TagA = nodeA->getTag();
	int TagB = nodeB->getTag();
	if (TagA == MyTag::PlayerAmmo_TAG)
		ammo = dynamic_cast<PistolAmmo*>(nodeA);
	else if (TagA == MyTag::Monster_TAG)
		monster = dynamic_cast<Monster*>(nodeA);
	else if (TagA == 0)
		player = dynamic_cast<Player*>(nodeA);
	else if (TagA == MyTag::MonsterAmmo_TAG)
		ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeA);

	if (TagB == MyTag::PlayerAmmo_TAG)
		ammo = dynamic_cast<PistolAmmo*>(nodeB);
	else if (TagB == MyTag::Monster_TAG)
		monster = dynamic_cast<Monster*>(nodeB);
	else if (TagB == 0)
		player = dynamic_cast<Player*>(nodeB);
	else if (TagB == MyTag::MonsterAmmo_TAG)
		ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeB);
	if ((TagB==MyTag::Monster_TAG&&TagA==MyTag::PlayerAmmo_TAG)|| (TagA == MyTag::Monster_TAG && TagB == MyTag::PlayerAmmo_TAG))//怪物撞玩家子弹
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
	if ((TagA==MyTag::Player_TAG&&TagB==MyTag::MonsterAmmo_TAG)|| (TagB == MyTag::Player_TAG && TagA == MyTag::MonsterAmmo_TAG))//玩家撞怪物子弹
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
