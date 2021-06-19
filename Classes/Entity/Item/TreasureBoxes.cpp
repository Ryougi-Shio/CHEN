#include"TreasureBoxes.h"
#include"AllTag.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"BattleMap.h"
#include"NormalBattleScene.h"
USING_NS_CC;
bool TreasureBoxes::init()
{
	bindSprite(Sprite::create("Items/box_1.png"));
	this->schedule(CC_SCHEDULE_SELECTOR(TreasureBoxes::update), 0.01f);

	return 1;
}
void TreasureBoxes::BoxBirth(int i)
{
	TMXObjectGroup* objGroup = mMap->getBattleMap()->getObjectGroup("Item");//��ȡ�����
	char s[40];

	sprintf(s, "Box_%d", i);
	auto BoxBirth = objGroup->getObject(s);//��ȡ����

	int x = BoxBirth.at("x").asInt();
	int y = BoxBirth.at("y").asInt();

	setPosition(Vec2(BoxBirth.at("x").asInt(), BoxBirth.at("y").asInt()));//����λ������


}
void TreasureBoxes::Interact(char s[])
{
	if (isAround(100))
	{
		if (!isOpen)//�ǹص�
		{
			bindSprite(Sprite::create("Items/box_2.png"));
			isOpen = 1;
			if (isUsed == 0&&isCanSee==1)//û�ù��ܿ���
			{
				notice(s);
				isUsed = 1;
				startTime = clock();

			}

		}
		else//�ǿ��� 
		{

			this->removeAllChildren();
			bindSprite(Sprite::create("Items/box_1.png"));

			isOpen = 0;
		}

	}

}
void TreasureBoxes::notice(char s[])
{
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel,10);
	noticeLabel->setOpacity(255);
	noticeLabel->setPosition(getPosition().x, getPosition().y + noticeLabel->getContentSize().height * 1.5);
}
void TreasureBoxes::update(float dt)
{
	if (isCanSee)
		this->getSprite()->setOpacity(255);
	else
		this->getSprite()->setOpacity(0);
	if (noticeLabel)
	{

		;
	}

}
bool TreasureBoxes::getIsOpen()
{
	return isOpen;
}