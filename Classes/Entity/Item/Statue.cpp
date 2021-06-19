#include "Statue.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"PlayerMove.h"
#include"AllTag.h"
#include"BattleMap.h"
bool Statue::init()
{
	this->bindSprite(Sprite::create("Items/StatuePaladin.png"));

	return true;
}

void Statue::Interact(int mode)
{
	//��
	/*������Ч����
	* �����˺�buff
	* �ӻ���
	* ���10��Ǯ
	*/
	if (isUsed == 0 )
	{
		isUsed = 1;
		char* s;
		mPlayer->getPlayerAttribute()->CutMoney(30);
		StatueType = rand() % 3;
		if (StatueType == 0)
		{
			s = "Damage Buff";
			mPlayer->getPlayerAttribute()->changeDamage_Buff(1);
		}

		else if (StatueType == 1)
		{
			s = "AP Healing";
			mPlayer->getPlayerAttribute()->changeAp(20);
		}

		else if (StatueType == 2)
		{
			s = "Add Money";
			mPlayer->getPlayerAttribute()->AddMoney(50);
		}

		this->ChangeNotice(s);
		

	}
	
}

void Statue::update(float dt)
{
	;
}

void Statue::notice(char s[])
{
	//�����Ӧ����ʾ��ǩ
	/*
	if (StatueType == 0)
		s = "Damage UP";
	else if (StatueType == 1)
		s = "Hp Healing";
	else if (StatueType == 2)
		s = "Add Money";
	*/
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(255);
	noticeLabel->setPosition(getPosition().x, getPosition().y - noticeLabel->getContentSize().height * 1.5);
}

void Statue::setType(int type)
{
	StatueType = type;
}

int Statue::getType()
{
	return StatueType;
}
