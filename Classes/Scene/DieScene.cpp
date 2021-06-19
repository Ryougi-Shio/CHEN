#include "DieScene.h"
#include"StartScene.h"
bool DieScene::init()
{
	auto background = Sprite::create("background/die.png");
	background->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(background);
	this->schedule(CC_SCHEDULE_SELECTOR(DieScene::remove), 7.0f);
	return true;
}

void DieScene::remove(float dt)
{
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(StartScene::create());

}
