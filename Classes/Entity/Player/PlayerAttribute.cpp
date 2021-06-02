#include"PlayerAttribute.h"
#include"Player/Player.h"
#define MaxHp 5
#define MaxAp 5
USING_NS_CC;
bool PlayerAttribute::init()
{
	bindSprite(Sprite::create("UI/attribute_UI.png"));
	getSprite()->setPosition(Vec2::ZERO);
	//hpUI
	char hps[7];
	sprintf(hps, "%d/%d", mhp, MaxHp);
	hpLabel = Label::createWithTTF(std::string(hps), "fonts/Marker Felt.ttf", 16);
	hpLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height - hpLabel->getContentSize().height);
	getSprite()->addChild(hpLabel);
	//apUI
	char aps[7];
	sprintf(aps, "%d/%d", map, MaxAp);
	apLabel = Label::createWithTTF(std::string(aps), "fonts/Marker Felt.ttf", 16);
	apLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
		hpLabel->getContentSize().height - apLabel->getContentSize().height);
	getSprite()->addChild(apLabel);
	//moneyUI
	char moneys[7];
	sprintf(moneys, "%d", mmoney);
	moneyLabel = Label::createWithTTF(std::string(moneys), "fonts/Marker Felt.ttf", 16);
	moneyLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
		hpLabel->getContentSize().height - apLabel->getContentSize().height - moneyLabel->getContentSize().height+3);
	getSprite()->addChild(moneyLabel);
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::DeadUpdate), 0.01f);
	scheduleUpdate();
	return 1;
}
//改变HP和AP的值
void PlayerAttribute::update(float dt)
{
	char hps[7];
	sprintf(hps, "%d/%d", mhp, MaxHp);
	hpLabel->setString(std::string(hps));
	char aps[7];
	sprintf(aps, "%d/%d", map, MaxAp);
	apLabel->setString(std::string(aps));
	char moneys[7];
	sprintf(moneys, "%d", mmoney);
	moneyLabel->setString(std::string(moneys));
}
//开始恢复
void PlayerAttribute::ApHealingStart(float dt)
{
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealing),1.0f);
}
//恢复护甲
void PlayerAttribute::ApHealing(float dt)
{
	if (map<MaxAp)
	{
		map++;
	}
	else
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealing));//停止回复
	}
}

void PlayerAttribute::takeDamage(int damage)
{
	if (map > 0 && damage <= map)//只减甲
	{
		map -= damage;
	}
	else if (map > 0 && damage > map)//减甲减血
	{
		damage -= map;
		map = 0;
		mhp -= damage;
	}
	else
	{
		mhp -= damage;//只有血了
	}
	isDamaged = 1;
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealingStart), 2.0f);
}

void PlayerAttribute::hpApMoneyinit(int hp, int ap)
{
	mhp = hp;
	map = ap;
	mmoney = 0;
}

int PlayerAttribute::getHp()
{
	return mhp;
}

int PlayerAttribute::getAp()
{
	return map;
}

int PlayerAttribute::getMoney()
{
	return mmoney;
}

void PlayerAttribute::bindPlayer(Player* player)
{
	mplayer = player;
}
void PlayerAttribute::DeadUpdate(float dt)
{
	if (mhp<=0)
	{
		mplayer->unscheduleAllCallbacks();
		mplayer->dead();
	}
}
int PlayerAttribute::mhp;
int PlayerAttribute::map;
int PlayerAttribute::mmoney;