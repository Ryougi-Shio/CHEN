#include"MapGate.h"
#include"Entity/Player/Player.h"
#include"Entity/Player/PlayerMove.h"
#define WIDTH 116
#define LENGTH 116
bool MapGate::init()
{
	bindSprite(Sprite::create("maps/transfergate.png"));
//	this->scheduleUpdate();//开启调用update函数的能力
	return true;
}

void MapGate::bindPlayer(Player* mPlayer)
{
	player = mPlayer;
}
bool MapGate::isAround(float Px, float Py)//判断玩家是否在周围
{
	float Gx = this->getPositionX();
	float Gy = this->getPositionY();
//	CCLOG("Player(%f,%f)", Px, Py);
//	CCLOG("Gate(%f,%f)", Gx, Gy);
	if ((Px >= Gx - WIDTH * 0.5) && (Px <= Gx + WIDTH * 0.5) && (Py >= Gy - LENGTH * 0.5) && (Py <= Gy + LENGTH * 0.5))
		return true;
	else
		return false;

}


void MapGate::notice()
{
	auto keymap = player->getplayermove()->getkeyMap();
	noticeLabel = Label::createWithTTF("E", "fonts/Marker Felt.ttf", 24);
	this->addChild(noticeLabel, 6);
	noticeLabel->setPosition(0, noticeLabel->getContentSize().height * 1.5);
	if (keymap[EventKeyboard::KeyCode::KEY_E])
	{
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//清理精灵帧缓存
		
	}
}

void MapGate::update(float delta)
{
	float Px = player->getPositionX();
	float Py = player->getPositionY();

	if (isAround(Px, Py))
	{


	}
	else
	{
		
	}
}
bool MapGate::getAble()
{
	return Able;
}
void MapGate::IsAble(bool able)
{
	if (Able != able)
	{
		if (able)
		{
			this->getSprite()->setOpacity(255);
			this->scheduleUpdate();
			Able = able;
		}
		else
		{
			this->getSprite()->setOpacity(0);
			this->unscheduleUpdate();
			Able = able;
		}

	}
	
}
