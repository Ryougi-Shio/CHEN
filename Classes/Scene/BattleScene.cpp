#include"BattleScene.h"
#include"cocos2d.h"
#include"json.h"
#include <stdlib.h>
#include <time.h> 
#include"Player/PlayerMove.h"
#include"Player/PlayerAttribute.h"
#include"Monster/Monster.h"
#include"Monster/CloseMonster/CloseMonster_1.h"
#include"Monster/CloseMonster/CloseMonster_2.h"
#include"Monster/CloseMonster/CloseMonster_3.h"
#include"Monster/CloseMonster/CloseMonster_4.h"
#include"PistolAmmo.h"
#include"Pistol.h"
#include"CCVector.h"
#include"music.h"
USING_NS_CC;
bool BattleScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	if (initWithPhysics()) {
		getPhysicsWorld()->setGravity(Vec2::ZERO);
		getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		getPhysicsWorld()->setSubsteps(20);
	}

	//背景图片精灵
	for (int i = 0; i < 9; i++)
	{
		auto backgroundSprite = Sprite::create("background/BattleScene.png");
		backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2 + backgroundSprite->getContentSize().width * (i % 3),
			origin.y + backgroundSprite->getContentSize().height / 2 + backgroundSprite->getContentSize().height * (i / 3));
		this->addChild(backgroundSprite, -1);
	}



	//更改bgm以及绑定tiledmap
	getmusicManager()->changeMusic("bgm/Room.mp3");
	srand((unsigned)time(NULL));
	for (int x = 0; x < 9; x++)
	{
		int i = rand() % 3;
		char s[40];
		sprintf(s, "maps/BattleScene%d.tmx", i);
		//m_map.pushBack(TMXTiledMap::create(s));
		//m_map.back()->setPosition(visibleSize.width / 2 * 0 + visibleSize.width * (x % 3), visibleSize.height / 2 * 0 + visibleSize.height * (x / 3));
	}
	//parentMap = m_map.at(0);
	addChild(parentMap);

	//设置按钮
	auto settings = MenuItemImage::create("ui/settings.png", "ui/settings.png", [&](Ref* sender) {
		getmusicManager()->effectPlay("effect/button.mp3");
		getmusicManager()->menu(this);
		});
	//位置位于右上角
	settings->setPosition(visibleSize.width - settings->getContentSize().width / 2, visibleSize.height - settings->getContentSize().height / 2);

	//菜单
	auto menu = Menu::create(settings, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 5);

	//玩家创建
	auto physicsBody = PhysicsBody::createBox(Size(40.0f, 40.0f),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	bindPlayer(Player::create());
	getPlayer()->addComponent(physicsBody); 
	getPlayer()->getPhysicsBody()->setCategoryBitmask(0x02);//0010
	getPlayer()->getPhysicsBody()->setCollisionBitmask(0x01);//0001
	getPlayer()->setPosition(64 * 4 + 32, 64 * 4 + 32);
	//getPlayer()->getplayermove()->bindMap(parentMap);//PlayerMove跟这个地图绑定
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//属性UI位置设置
	this->addChild(getPlayer()->getPlayerAttribute(), 5);
	this->addChild(getPlayer(), 2);


	//近战怪物创建
	 Monster_1 =  CloseMonster_1::create();
	 Monster_1->bindScene(this);
	 Monster_1->Birth("Monster_birth1");
	 Monster_1->setTag(1);
	this->addChild( Monster_1, 4);
	auto physicsBody_M_1 = PhysicsBody::createBox(Size(46.0f, 48.0f),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	Monster_1->addComponent(physicsBody_M_1);
	Monster_1->getPhysicsBody()->setDynamic(false);
	Monster_1->getPhysicsBody()->setCategoryBitmask(0x0001);//0011
	Monster_1->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
	Monster_1->getPhysicsBody()->setContactTestBitmask(0x0001);


	CloseMonster_2* Monster_2 = CloseMonster_2::create();
	Monster_2->bindScene(this);
	Monster_2->Birth("Monster_birth2");
	this->addChild(Monster_2, 4);

	CloseMonster_3* Monster_3 = CloseMonster_3::create();
	Monster_3->bindScene(this);
	Monster_3->Birth("Monster_birth3");
	this->addChild(Monster_3, 4);

	CloseMonster_4* Monster_4 = CloseMonster_4::create();
	Monster_4->bindScene(this);
	Monster_4->Birth("Monster_birth4");
	this->addChild(Monster_4, 4);

	//传送门创建
	safeGate = Gate::create();
	safeGate->setPosition(64 * 9.45, 64 * 10);
	safeGate->bindPlayer(getPlayer());
	//safeGate->bindStart(this);
	//safeGate->bindDestination(this);
	//this->addChild(safeGate, 5);

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
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::test), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::DeleteAmmo), 0.01f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::Ammoupdate), getPlayer()->getWeapon1()->getShootSpeed());
	changeMap(2);
	return 1;
}
bool BattleScene::isWall(float x,float y)
{
	int mapX = (int)(x / 64);
	int mapY = (int)(12 - y / 64);

	//int tileGid = parentMap->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
	//CCLOG("X:%d    Y:%d", mapX, mapY);
	//CCLOG("%d", tileGid);
	//if (tileGid)
	{
		return true;	//是墙
	}

	//else
	{
		return false;		//不是墙
	}
}
void BattleScene::DeleteAmmo(float dt)
{
	if (AmmoList.size()!=0)
	{
		int i = 0;
		auto ix = AmmoList.begin();
		int size = AmmoList.size();
		for (; i<size;ix++,i++)
		{
			//CCLOG("size:%d  i=%d", size,i);
			if (isWall((*ix)->getPositionX(), (*ix)->getPositionY()))
			{
				removeChild(AmmoList[i]);
				AmmoList.erase(ix);
				break;
			}

		}
	}
	
}
bool BattleScene::onContactBegin(PhysicsContact& contact)
{
	PistolAmmo* ammo;
	Monster* monster;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == 10)
	{
		ammo = dynamic_cast<PistolAmmo*>(nodeA);
	}
	else if (nodeA->getTag() == 1)
	{
		monster = dynamic_cast<Monster*>(nodeA);
	}
	if (nodeB->getTag() == 10)
	{
		ammo = dynamic_cast<PistolAmmo*>(nodeB);
	}
	else if (nodeB->getTag() == 1)
	{
		monster = dynamic_cast<Monster*>(nodeB);
	}
	if (nodeA && nodeB)
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
	return true;
}
void BattleScene::update(float dt)
{
	//调用Player的update，Player的update再调用PlayMove的move函数
	getPlayer()->update(dt);
	
	//safeGate->update(dt);
}
void BattleScene::Ammoupdate(float dt)
{
	float x = getPlayer()->getMouseLocation().x;
	float y = Director::getInstance()->getVisibleSize().height - getPlayer()->getMouseLocation().y;
	float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
	float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
	float Wx = (Px + getPlayer()->getWeapon1()->getPositionX() + getPlayer()->getWeapon1()->getContentSize().width / 2);
	float Wy = (Py + getPlayer()->getWeapon1()->getPositionY());
	Vec2 v = Vec2(Vec2(x - Wx, y - Wy) / sqrt((x - Wx) * (x - Wx) + (y - Wy) * (y - Wy)));
	//CCLOG("%f %f", Px, Py);
	if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT])
	{
		AmmoList.push_back(getPlayer()->getWeapon1()->Attack());
		AmmoList.back()->setTag(10);
		addChild(AmmoList.back());
		auto physicBody = PhysicsBody::createBox(Size(10.0f, 10.0f), PhysicsMaterial(0, 0, 0));
		AmmoList.back()->addComponent(physicBody);
		//AmmoList.back()->getPhysicsBody()->setDynamic(false);
		AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
		AmmoList.back()->getPhysicsBody()->setVelocity(v*500);
		AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
		AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
		AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
	}
	

}
void BattleScene::test(float dt)
{
	//Monster_1->takingDamage(1);
}