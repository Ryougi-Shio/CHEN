#include"BattleScene.h"
#include"cocos2d.h"
#include"json.h"
#include <stdlib.h>
#include <time.h> 
USING_NS_CC;
bool BattleScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	//背景图片精灵
	auto backgroundSprite = Sprite::create("background/BattleScene.png");
	backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2, origin.y + backgroundSprite->getContentSize().height / 2);
	this->addChild(backgroundSprite, -1);



	//更改bgm以及绑定tiledmap
	getmusicManager()->changeMusic("bgm/Room.mp3");
	srand((unsigned)time(NULL));
	int i = rand()%3;
	char s[40];
	sprintf(s, "maps/BattleScene%d.tmx", i);
	map = TMXTiledMap::create(s);
	bindTiledMap(map);

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
	player = Player::create();
	player->setPosition(64 * 4 + 32, 64 * 4 + 32);
	player->getplayermove()->bindMap(map);//PlayerMove跟这个地图绑定
	this->addChild(player, 2);

	//传送门创建
	safeGate = Gate::create();
	safeGate->setPosition(64 * 9.45, 64 * 10);
	safeGate->bindPlayer(player);
	safeGate->bindStart(this);
	safeGate->bindDestination(this);
	//this->addChild(safeGate, 5);

	////eventlistener,键盘监听，用于移动人物
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘按下时响应
	{
		player->getplayermove()->TrueKeyCode(keycode);//PlayerMove里keyMap的对应键码置true

	};

	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘松开时响应
	{
		player->getplayermove()->FalseKeyCode(keycode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	this->scheduleUpdate();


	return 1;
}
void BattleScene::update(float dt)
{
	//调用Player的update，Player的update再调用PlayMove的move函数（禁止套娃）
	//isWall(player->getPositionX(), player->getPositionY())

	player->update(dt);
	//safeGate->update(dt);
}