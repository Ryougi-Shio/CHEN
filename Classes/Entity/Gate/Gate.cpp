#include"Gate.h"
#include"NormalScene.h"
#include"BattleScene.h"
#include"Player.h"
#define WIDTH 116
#define LENGTH 116
USING_NS_CC;
bool Gate::init()
{
	bindSprite(Sprite::create("maps/transfergate.png"));
	//this->scheduleUpdate();//��������update����������
	return true;
}
void Gate::bindPlayer(Player* mPlayer)
{
	player = mPlayer;
}
bool Gate::isAround(float Px, float Py)
{
	float Gx = this->getPositionX();
	float Gy = this->getPositionY();
	if ((Px >= Gx - WIDTH * 0.5) && (Px <= Gx + WIDTH * 0.5) && (Py >= Gy - LENGTH * 0.5) && (Py <= Gx + LENGTH * 0.5))
		return true;
	else
		return false;

}
/*
void Gate::transferMenu()
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//UI����ͼƬ
	auto UIbackground = Sprite::create("UI/TransferUI.png");
	UIbackground->setPosition(visibleSize / 2);
	this->addChild(UIbackground);

	//���ذ�ť
	auto back= MenuItemImage::create("UI/false_button.png", "UI/false_button.png", [&](Ref* sender) {
		start->getmusicManager()->effectPlay("effect/button.mp3");
		this->removeChild(UIbackground);
		});
	back->setPosition(Vec2(200,170));

	auto menu = Menu::create(back, nullptr);
	menu->setPosition(Vec2::ZERO);
	UIbackground->addChild(menu);
	
}*/
void Gate::bindStart(NormalScene* mScene)
{
	start = mScene;
}
void Gate::bindDestination(NormalScene* mScene)
{
	destination = mScene;
}
NormalScene* Gate::getStart()
{
	return start;
}
NormalScene* Gate::getDestination()
{
	return destination;
}

void Gate::notice()
{
	auto keymap = player->getplayermove()->getkeyMap();
	noticeLabel = Label::createWithTTF("E", "fonts/Marker Felt.ttf",24);
	start->addChild(noticeLabel,6);
	noticeLabel->setPosition(getPosition().x, getPosition().y + noticeLabel->getContentSize().height * 1.5);
	if (keymap[EventKeyboard::KeyCode::KEY_E])
	{
		Director::getInstance()->replaceScene(BattleScene::create());
	}
}

void Gate::update(float delta)
{
	float Px = player->getPositionX();
	float Py = player->getPositionY();
	if (isAround(Px, Py))
	{
		notice();
	}
	else
	{
		start->removeChild(noticeLabel);
	}
}