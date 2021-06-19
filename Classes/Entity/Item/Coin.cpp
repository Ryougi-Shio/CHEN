#include"Coin.h"
#include"cocos2d.h"
#include"Player.h"
#include"PlayerAttribute.h"
#include"AllTag.h"
#include"BattleMap.h"
#include"music.h"
USING_NS_CC;
bool  Coin::init()
{
	//钱币 持续播放动画循环
	this->bindSprite(Sprite::create("Items/coin_1.png")); 
	Animation* animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "Items/coin_%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}

	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);

	auto* action = Animate::create(animation);
	action->retain();
	this->getSprite()->runAction(action);

	return 1;
}
void Coin::Interact(int mode)
{	
	//biling音效  捡起+10money
	MusicManager::effectPlay("effect/money.mp3");
	mPlayer->getPlayerAttribute()->AddMoney(10);
	isUsed = 1;
	isCanSee = 1;
}
void Coin::update(float dt)
{
	;
}
void Coin::notice(char s[])
{
	noticeLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);

	noticeLabel->setTag(NoticeLabel_TAG);
	mMap->addChild(noticeLabel, 10);
	noticeLabel->setOpacity(0);
	noticeLabel->setPosition(getPosition().x, getPosition().y - noticeLabel->getContentSize().height * 1.5);
}