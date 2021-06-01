#include"MapGate.h"
#include"Entity/Player/Player.h"
#include"Entity/Player/PlayerMove.h"
#define WIDTH 116
#define LENGTH 116
bool MapGate::init()
{
	bindSprite(Sprite::create("maps/transfergate.png"));
	this->scheduleUpdate();//��������update����������
	return true;
}

void MapGate::bindPlayer(Player* mPlayer)
{
	player = mPlayer;
}
bool MapGate::isAround(float Px, float Py)//�ж�����Ƿ�����Χ
{
	float Gx = this->getPositionX();
	float Gy = this->getPositionY();
	if ((Px >= Gx - WIDTH * 0.5) && (Px <= Gx + WIDTH * 0.5) && (Py >= Gy - LENGTH * 0.5) && (Py <= Gx + LENGTH * 0.5))
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
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//������֡����
		;
	}
}

void MapGate::update(float delta)
{
	float Px = player->getPositionX();
	float Py = player->getPositionY();
	if (isAround(Px, Py))
	{
		notice();
	}
	else
	{
		;//�˴�Ӧ���notice����Ŀǰû�а취
	}
}

