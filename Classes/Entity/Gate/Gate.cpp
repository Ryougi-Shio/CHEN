#include"Gate.h"
#include"NormalScene.h"
#include"BattleScene1.h"
#include"Player.h"
#include"Player/PlayerMove.h"
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
bool Gate::isAround(float Px, float Py)//�ж�����Ƿ�����Χ
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
//��ʾ��'E'��ĿǰBUG�����Զ�����ʾ������ʧ
void Gate::notice()
{
	auto keymap = player->getplayermove()->getkeyMap();
	noticeLabel = Label::createWithTTF("E", "fonts/Marker Felt.ttf",24);
	start->addChild(noticeLabel,6);
	noticeLabel->setPosition(getPosition().x, getPosition().y + noticeLabel->getContentSize().height * 1.5);
	if (keymap[EventKeyboard::KeyCode::KEY_E])
	{
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//������֡����
		Director::getInstance()->replaceScene(BattleScene1::create());
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
		;//�˴�Ӧ���notice����Ŀǰû�а취
	}
}