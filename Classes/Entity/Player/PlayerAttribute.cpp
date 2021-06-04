#include"PlayerAttribute.h"
#include"Player/Player.h"
#include"json/json.h"
USING_NS_CC;
bool PlayerAttribute::init()
{
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("json/Hero.json");
	if (reader.parse(data, root, false) == true)
	{
//		CCLOG("%d", root.isMember("knight"));
		if (strlen(heroName) == 0)
		{
			changeHero("knight");
		}
		maxHp = root[heroName]["Hp"].asInt();
		maxAp = root[heroName]["Ap"].asInt();
	}
	bindSprite(Sprite::create("UI/attribute_UI.png"));
	getSprite()->setPosition(Vec2::ZERO);
	//hpUI
	char hps[20];
	sprintf(hps, "%d/%d", mhp, maxHp);
	hpLabel = Label::createWithTTF(std::string(hps), "fonts/Marker Felt.ttf", 16);
	hpLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height - hpLabel->getContentSize().height);
	getSprite()->addChild(hpLabel);
	//apUI
	char aps[20];
	sprintf(aps, "%d/%d", map, maxAp);
	apLabel = Label::createWithTTF(std::string(aps), "fonts/Marker Felt.ttf", 16);
	apLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
		hpLabel->getContentSize().height - apLabel->getContentSize().height);
	getSprite()->addChild(apLabel);
	//moneyUI
	char moneys[20];
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
	char hps[20];
	sprintf(hps, "%d/%d", mhp, maxHp);
	hpLabel->setString(std::string(hps));
	char aps[20];
	sprintf(aps, "%d/%d", map, maxAp);
	apLabel->setString(std::string(aps));
	char moneys[20];
	sprintf(moneys, "%d", mmoney);
	moneyLabel->setString(std::string(moneys));
}
void PlayerAttribute::resetColor(float delay)
{
	mplayer->getSprite()->setColor(Color3B(255, 255, 255));
}
//开始恢复
void PlayerAttribute::ApHealingStart(float dt)
{
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealing),1.0f);
}
//恢复护甲
void PlayerAttribute::ApHealing(float dt)
{
	if (map<maxAp)
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
	mplayer->getSprite()->setColor(Color3B(255, 0, 0));
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(PlayerAttribute::resetColor), 0.1f);
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

void PlayerAttribute::hpApMoneyinit()
{
	mhp = maxHp;
	map = maxAp;
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
void PlayerAttribute::changeHero(char hero[])
{
	strcpy(heroName, hero);
}
int PlayerAttribute::mhp;
int PlayerAttribute::map;
int PlayerAttribute::mmoney;
char PlayerAttribute::heroName[10];