#include"SafeScene.h"
#include"cocos2d.h"
#include"json.h"
#include"Player/PlayerAttribute.h"
#include"Player/PlayerMove.h"
#include"Sword.h"
#include"Pistol.h"
#include"PitchFork.h"
#include"HeroNPC.h"
#include"AllTag.h"
USING_NS_CC;
bool SafeScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	//背景图片精灵
	auto backgroundSprite = Sprite::create("background/SafeScene.png");
	backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2, origin.y + backgroundSprite->getContentSize().height / 2);
	this->addChild(backgroundSprite,1);

	//更改bgm以及绑定tiledmap
	getmusicManager()->changeMusic("bgm/Room.mp3");
	map = TMXTiledMap::create("maps/SafeScene.tmx");
	bindTiledMap(map);

	//设置按钮
	auto settings = MenuItemImage::create("ui/settings.png", "ui/settings.png", [&](Ref* sender) {
		getmusicManager()->effectPlay("effect/button.mp3");
		getmusicManager()->menu(this);

	});
	//位置位于右上角
	settings->setPosition(visibleSize.width - settings->getContentSize().width / 2, visibleSize.height - settings->getContentSize().height/2);

	//菜单
	auto menu = Menu::create(settings, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,5);

	//玩家创建
	bindPlayer(Player::create());
	getPlayer()->PistolInit();//手枪
//	getPlayer()->ShotgunInit();//霰弹枪
//	getPlayer()->SwordInit();//剑
//	getPlayer()->PitchForkInit();//干草叉

	getPlayer()->getPlayerAttribute()->HpApMoneySpeedDamageinit();//玩家属性初始化
	getPlayer()->getPlayerAttribute()->Buffinit();//玩家buff初始化（全是0
	getPlayer()->setPosition(64 * 4 + 32, 64 * 4 + 32);
	getPlayer()->getplayermove()->bindMap(map);//PlayerMove跟这个地图绑定
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//属性UI位置设定
	this->addChild(getPlayer()->getPlayerAttribute(),5);//生成playerUI
	this->addChild(getPlayer(),2);
	//
	heroNPC = HeroNPC::create();
	this->addChild(heroNPC,10);

	heroNPC->setPosition(64*5,64*5);

	//传送门创建

	safeGate = Gate::create();
	safeGate->setPosition(64*9.45,64*10);
	safeGate->bindPlayer(getPlayer());
	safeGate->bindStart(this);
//	safeGate->notice();

	//safeGate->bindDestination(BattleScene::create());
	this->addChild(safeGate, 5);

	////eventlistener,键盘监听，用于移动人物
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘按下时响应
	{
		if (keycode==EventKeyboard::KeyCode::KEY_E)
		{
			int x = getPlayer()->getPositionX();
			int y = getPlayer()->getPositionY();
			int Nx = heroNPC->getPositionX();
			int Ny = heroNPC->getPositionY();
			if (sqrt((x - Nx) * (x - Nx) + (y - Ny) * (y - Ny)) <= 100)
			{

				if (getPlayer()->getTag() == Hero_Knight_TAG)
				{
					getPlayer()->changeHero("ranger");
					getPlayer()->getPlayerAttribute()->HpApMoneySpeedDamageinit();
					heroNPC->interact(0);
				}

				else
				{
					getPlayer()->changeHero("knight");
					getPlayer()->getPlayerAttribute()->HpApMoneySpeedDamageinit();
					heroNPC->interact(1);
				}

			}
		}

		if (keycode==EventKeyboard::KeyCode::KEY_R)
		{
			getPlayer()->getPlayerAttribute()->LevelUp();
		}
		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove里keyMap的对应键码置true
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




	this->scheduleUpdate();
	//this->schedule(CC_SCHEDULE_SELECTOR(SafeScene::test), 10.0f);
	//this->schedule(CC_SCHEDULE_SELECTOR(SafeScene::ChangeHeroUpdate), 0.1f);

	return 1;
}

void SafeScene::update(float dt)
{
	//调用Player的update，Player的update再调用PlayMove的move函数（禁止套娃）
	//isWall(player->getPositionX(), player->getPositionY())
	

	safeGate->update(dt);
}

void SafeScene::ChangeHeroUpdate(float dt)
{
	;
}

void SafeScene::test(float dt)
{
	getPlayer()->getPlayerAttribute()->takeDamage(5);
}

