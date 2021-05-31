#include"SafeScene.h"
#include"BattleScene.h"
#include"cocos2d.h"
#include"json.h"
#include"Player/PlayerAttribute.h"
#include"Player/PlayerMove.h"
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
	getPlayer()->getPlayerAttribute()->hpApMoneyinit(5, 5);//������Գ�ʼ��
	getPlayer()->setPosition(64 * 4 + 32, 64 * 4 + 32);
	getPlayer()->getplayermove()->bindMap(map);//PlayerMove�������ͼ��
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//����UIλ���趨
	this->addChild(getPlayer()->getPlayerAttribute(),5);//����playerUI
	this->addChild(getPlayer(),2);



	//�����Ŵ���

	safeGate = Gate::create();
	safeGate->setPosition(64*9.45,64*10);
	safeGate->bindPlayer(getPlayer());
	safeGate->bindStart(this);
	//safeGate->bindDestination(BattleScene::create());
	this->addChild(safeGate, 5);

	////eventlistener,���̼����������ƶ�����
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//���̰���ʱ��Ӧ
	{

		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove��keyMap�Ķ�Ӧ������true

	};

	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//�����ɿ�ʱ��Ӧ
	{
		getPlayer()->getplayermove()->FalseKeyCode(keycode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	this->scheduleUpdate();
	//this->schedule(CC_SCHEDULE_SELECTOR(SafeScene::test), 10.0f);
	return 1;
}

void SafeScene::update(float dt)
{
	//����Player��update��Player��update�ٵ���PlayMove��move��������ֹ���ޣ�
	//isWall(player->getPositionX(), player->getPositionY())
	
	getPlayer()->update(dt);
	safeGate->update(dt);
}

void SafeScene::test(float dt)
{
	getPlayer()->getPlayerAttribute()->takeDamage(5);
}

