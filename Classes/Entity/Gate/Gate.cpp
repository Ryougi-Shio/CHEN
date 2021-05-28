#include"Gate.h"
#include"NormalScene.h"
#include"Player.h"
#define WIDTH 116
#define LENGTH 116
USING_NS_CC;
bool Gate::init()
{
	bindSprite(Sprite::create("maps/transfergate.png"));
	this->scheduleUpdate();//开启调用update函数的能力
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
void Gate::transferMenu(NormalScene* start, NormalScene* destination)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//UI背景图片
	auto UIbackground = Sprite::create("UI/TransferUI.png");
	UIbackground->setPosition(visibleSize / 2);
	start->addChild(UIbackground, 5);

	//返回按钮
	auto back= MenuItemImage::create("UI/false_button.png", "UI/false_button.png", [&](Ref* sender) {
		start->getmusicManager()->effectPlay("effect/button.mp3");
		start->removeChild(UIbackground);
		});
	back->setPosition(Vec2(200,170));
	UIbackground->addChild(back);

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
void Gate::update(float delta)
{
	float Px = player->getPositionX();
	float Py = player->getPositionY();
	if (isAround(Px, Py))
	{
		transferMenu(start,destination);
	}
}