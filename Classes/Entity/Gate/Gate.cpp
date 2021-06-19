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
	if ((Px >= Gx - WIDTH * 0.5) && (Px <= Gx + WIDTH * 0.5) && (Py >= Gy - LENGTH * 0.5) && (Py <= Gy + LENGTH * 0.5))
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
	
	if (!isOn)
	{
		noticeLabel = Label::createWithTTF(Content, "fonts/Marker Felt.ttf", 24);
		start->addChild(noticeLabel, 6);
		noticeLabel->setTag(NoticeLabel_TAG);
		noticeLabel->setPosition(getPosition().x, getPosition().y + noticeLabel->getContentSize().height * 1.5);
	}

		
	
	if (keymap[EventKeyboard::KeyCode::KEY_E])
	{
		MusicManager::effectPlay("effect/tp.mp3");
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//������֡����
		Director::getInstance()->replaceScene(BattleScene1::create());
	}
	isOn = 1;
	

}

void Gate::update(float delta)
{
	float Px = player->getPositionX();
	float Py = player->getPositionY();
	if (isAround(Px, Py))
	{
		Content = "E";
		notice();

	}
	else
	{
		start->removeChildByTag(NoticeLabel_TAG);//���ݱ�ǩremove
		isOn = 0;
	}

}