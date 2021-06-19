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
	
	//����ͼƬ����
	auto backgroundSprite = Sprite::create("background/SafeScene.png");
	backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2, origin.y + backgroundSprite->getContentSize().height / 2);
	this->addChild(backgroundSprite,1);

	//����bgm�Լ���tiledmap
	getmusicManager()->changeMusic("bgm/Room.mp3");
	map = TMXTiledMap::create("maps/SafeScene.tmx");
	bindTiledMap(map);

	//���ð�ť
	auto settings = MenuItemImage::create("ui/settings.png", "ui/settings.png", [&](Ref* sender) {
		getmusicManager()->effectPlay("effect/button.mp3");
		getmusicManager()->menu(this);

	});
	//λ��λ�����Ͻ�
	settings->setPosition(visibleSize.width - settings->getContentSize().width / 2, visibleSize.height - settings->getContentSize().height/2);

	//�˵�
	auto menu = Menu::create(settings, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,5);

	//��Ҵ���
	bindPlayer(Player::create());
	getPlayer()->PistolInit();//��ǹ
//	getPlayer()->ShotgunInit();//����ǹ
//	getPlayer()->SwordInit();//��
//	getPlayer()->PitchForkInit();//�ɲݲ�

	getPlayer()->getPlayerAttribute()->HpApMoneySpeedDamageinit();//������Գ�ʼ��
	getPlayer()->getPlayerAttribute()->Buffinit();//���buff��ʼ����ȫ��0
	getPlayer()->setPosition(64 * 4 + 32, 64 * 4 + 32);
	getPlayer()->getplayermove()->bindMap(map);//PlayerMove�������ͼ��
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//����UIλ���趨
	this->addChild(getPlayer()->getPlayerAttribute(),5);//����playerUI
	this->addChild(getPlayer(),2);
	//
	heroNPC = HeroNPC::create();
	this->addChild(heroNPC,10);

	heroNPC->setPosition(64*5,64*5);

	//�����Ŵ���

	safeGate = Gate::create();
	safeGate->setPosition(64*9.45,64*10);
	safeGate->bindPlayer(getPlayer());
	safeGate->bindStart(this);
//	safeGate->notice();

	//safeGate->bindDestination(BattleScene::create());
	this->addChild(safeGate, 5);

	////eventlistener,���̼����������ƶ�����
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//���̰���ʱ��Ӧ
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
		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove��keyMap�Ķ�Ӧ������true
	};

	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//�����ɿ�ʱ��Ӧ
	{
		getPlayer()->getplayermove()->FalseKeyCode(keycode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	//������
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseMove = [=](cocos2d::Event* event)//�ƶ�
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->changeMouseLocation(e->getLocation());


	};
	myMouseListener->onMouseDown = [=](cocos2d::Event* event)//����
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->trueMouseMap(e->getMouseButton());

	};
	myMouseListener->onMouseUp = [=](cocos2d::Event* event)//�ɿ�
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
	//����Player��update��Player��update�ٵ���PlayMove��move��������ֹ���ޣ�
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

