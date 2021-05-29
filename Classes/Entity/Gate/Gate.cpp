#include"Gate.h"
#include"NormalScene.h"
#include"BattleScene.h"
#include"Player.h"
#include"Player/PlayerMove.h"
#define WIDTH 116
#define LENGTH 116
USING_NS_CC;
bool Gate::init()
{
	bindSprite(Sprite::create("maps/transfergate.png"));
	//this->scheduleUpdate();//开启调用update函数的能力
	return true;
}
void Gate::bindPlayer(Player* mPlayer)
{
	player = mPlayer;
}
bool Gate::isAround(float Px, float Py)//判断玩家是否在周围
{
	float Gx = this->getPositionX();
	float Gy = this->getPositionY();
	if ((Px >= Gx - WIDTH * 0.5) && (Px <= Gx + WIDTH * 0.5) && (Py >= Gy - LENGTH * 0.5) && (Py <= Gx + LENGTH * 0.5))
		return true;
	else
		return false;

}

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
//提示按'E'，目前BUG：玩家远离后提示不会消失
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
		;//此处应清除notice，但目前没有办法
	}
}