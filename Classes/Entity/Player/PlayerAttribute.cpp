#include"PlayerAttribute.h"
#include"Player/Player.h"
#include"json/json.h"
#include"Entity.h"
#include"music.h"
#include <direct.h>
USING_NS_CC;
bool PlayerAttribute::init()
{
	
	changeAttribute();
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::DeadUpdate), 0.01f);
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::CountTimeUpdate), 0.01f);
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::Skill_EffectUpdate), 0.5f);
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::Buff_EffectUpdate), 0.05f);
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::BurningUpdate), 1.0f);
	//Effect

	SkillEffect = Sprite::create("CharacterEffect/blank.png");
	SkillEffect->setScale(2);
	scheduleUpdate();

	BuffEffect = Sprite::create("CharacterEffect/Damage.png");
	BuffEffect->setOpacity(0);
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
	char scores[20];
	sprintf(scores, "scores: %d", mscore);
	mscoreLabel->setString(scores);
	char levels[20];
	sprintf(levels, "level: %d", level);
	levelLabel->setString(levels);
}
void PlayerAttribute::resetColor(float delay)
{
	if(!isBurning)
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
	if (map<maxAp&&!isDamaged)
	{
		map++;

	}
	else
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealing));//停止回复
		isDamaged = 1;
	}
}

void PlayerAttribute::takeDamage(int damage)
{
	MusicManager::effectPlay("effect/player_damage.mp3");
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
	startTime = clock();
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(PlayerAttribute::ApHealingStart), 2.0f);
}
void PlayerAttribute::AddHp(int heal)
{
	mhp += heal;
	mhp = mhp > maxHp ? maxHp : mhp;
}
void PlayerAttribute::AddScore(int score)
{
	mscore += score;
}
void PlayerAttribute::CutScore(int score)
{
	mscore -= score;

}
void PlayerAttribute::HpApMoneySpeedDamageinit()
{
	mhp = maxHp;
	map = maxAp;
	mmoney = 0;
	damage = 2;
	shootSpeed = 0;//输入时单位为ms
	isDamaged = 0;
}
void PlayerAttribute::Buffinit()//Buff初始化为0
{
	Hp_buff = 0;
	Ap_buff = 0;
	damage_buff = 0;
	shootSpeed_buff = 0;
}
//获取人物各项属性
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
int PlayerAttribute::getDamage()
{
	return damage;
}
int PlayerAttribute::getShootSpeed()
{
	return shootSpeed;
}
int PlayerAttribute::getScore()
{
	return mscore;
}
void PlayerAttribute::changeHp(int n)
{
	mhp += n;
}
void PlayerAttribute::changeAp(int n)
{
	map += n;
}
void PlayerAttribute::changeMoney(int n)
{
	mmoney += n;
}
void PlayerAttribute::changeDamage(int n)
{
	damage += n;
}
void PlayerAttribute::changeShootSpeed(int n)
{
	shootSpeed += n;
}

void PlayerAttribute::changeScore(int n)
{
	mscore = n;
}


//获取各项buff属性
int PlayerAttribute::getHp_Buff()
{
	return Hp_buff;
}
int PlayerAttribute::getAp_Buff()
{
	return Ap_buff;
}
int PlayerAttribute::getDamage_Buff()
{
	return damage_buff;
}
int PlayerAttribute::getShootSpeed_Buff()
{
	return shootSpeed_buff;
}

//设置buff
void PlayerAttribute::changeHp_Buff(int buff)
{
	Hp_buff += buff;
}
void PlayerAttribute::changeAp_Buff(int buff)
{
	Ap_buff += buff;
}
void PlayerAttribute::changeDamage_Buff(int buff)
{
	damage_buff += buff;
}
void PlayerAttribute::changeShootSpeed_Buff(int buff)
{
	shootSpeed_buff += buff;	
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

	if(this!=nullptr)
		changeAttribute();
}
void PlayerAttribute::AddMoney(int income)
{
	mmoney += income;
}
bool PlayerAttribute::CutMoney(int outcome)
{
	if (mmoney >= outcome)
	{
		mmoney -=outcome;
		return true;
	}
	else
	{
		return false;
	}

}
void PlayerAttribute::CountTimeUpdate(float dt)
{
	if (clock() - startTime > 2000)
	{
		isDamaged = 0;
	}
}
void PlayerAttribute::Skill_EffectUpdate(float dt)
{
	if (shootSpeed_buff)//有射速buff，着火特效
	{
		Animation* animation = Animation::create();
		for (int i = 1; i <= 6; i++)
		{
			char s[50];
			sprintf(s, "CharacterEffect/flame_effect%d.png", i);
			animation->addSpriteFrameWithFile(s);
		}
		animation->setDelayPerUnit(0.1f);
		auto* action = Animate::create(animation);
		SkillEffect->runAction(action);
	}

	
}
void PlayerAttribute::Buff_EffectUpdate(float dt)
{
	if (damage_buff)//有伤害buff，
	{
		BuffEffect->setOpacity(255);
	}
	else
		BuffEffect->setOpacity(0);
}
Sprite* PlayerAttribute::getSkillEffect()
{
	return SkillEffect;
}
Sprite* PlayerAttribute::getBuffEffect()
{
	return BuffEffect;
}
void PlayerAttribute::LevelUp()
{
	if (mscore>=290)
	{
		mscore -= 290;
		{
			UserDefault::getInstance()->setIntegerForKey("Score", mscore);
			UserDefault::getInstance()->flush();
		}
		level += 1;
		{
			char s[100];
			sprintf(s,"%sLevel", heroName);
			UserDefault::getInstance()->setIntegerForKey(s,level);
			UserDefault::getInstance()->flush();
		}
		changeAttribute();
		HpApMoneySpeedDamageinit();
	}
}
void PlayerAttribute::setIsBurnging(int burn)
{
	isBurning = burn;
}
bool PlayerAttribute::getIsBurning()
{
	return isBurning;
}
void PlayerAttribute::BurningUpdate(float dt)
{
	if (isBurning)
	{
		this->takeDamage(1);
		
	}
	else
	{
		;
	}
}
void PlayerAttribute::changeAttribute()
{
	char* currentPaths;
	currentPaths = getcwd(NULL, 0);
	{
		char s[200];
		sprintf(s, "%sLevel", heroName);
		level = UserDefault::getInstance()->getIntegerForKey(s);
		if (level==NULL)
		{
			UserDefault::getInstance()->setIntegerForKey(s, 1);
			level = UserDefault::getInstance()->getIntegerForKey(s);
			UserDefault::getInstance()->flush();
		}
	}
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
			maxHp = root[heroName]["Hp"].asInt() + (level - 1) * 10;
			maxAp = root[heroName]["Ap"].asInt() + (level - 1) * 10;
		}
	}
	if (getSprite() == NULL)
	{
		bindSprite(Sprite::create("UI/attribute_UI.png"));
		getSprite()->setPosition(Vec2::ZERO);
	}
	//hpUI
	if (hpLabel==nullptr)
	{
		char hps[20];
		sprintf(hps, "%d/%d", mhp, maxHp);
		hpLabel = Label::createWithTTF(std::string(hps), "fonts/Marker Felt.ttf", 16);
		hpLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height - hpLabel->getContentSize().height);
		getSprite()->addChild(hpLabel,2);
	}
	//apUI
	if (apLabel==NULL)
	{
		char aps[20];
		sprintf(aps, "%d/%d", map, maxAp);
		apLabel = Label::createWithTTF(std::string(aps), "fonts/Marker Felt.ttf", 16);
		apLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
			hpLabel->getContentSize().height - apLabel->getContentSize().height);
		getSprite()->addChild(apLabel);
	}
	//moneyUI
	if (moneyLabel==NULL)
	{
		char moneys[20];
		sprintf(moneys, "%d", mmoney);
		moneyLabel = Label::createWithTTF(std::string(moneys), "fonts/Marker Felt.ttf", 16);
		moneyLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
			hpLabel->getContentSize().height - apLabel->getContentSize().height - moneyLabel->getContentSize().height + 3);
		getSprite()->addChild(moneyLabel);
	}
	//HpApMoneySpeedDamageinit();
	{
		mscore = UserDefault::getInstance()->getIntegerForKey("Score");
	}
	if (mscoreLabel == NULL)
	{
		char scores[20];
		sprintf(scores, "scores: %d", mscore);
		mscoreLabel = Label::createWithTTF(scores, "fonts/Marker Felt.ttf", 24);
		mscoreLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
			hpLabel->getContentSize().height - apLabel->getContentSize().height - moneyLabel->getContentSize().height -
			mscoreLabel->getContentSize().height + 3);
		getSprite()->addChild(mscoreLabel);
	}
	if (levelLabel == NULL)
	{
		char levels[20];
		sprintf(levels, "level: %d", level);
		levelLabel = Label::createWithTTF(levels, "fonts/Marker Felt.ttf", 24);
		levelLabel->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height -
			hpLabel->getContentSize().height - apLabel->getContentSize().height - moneyLabel->getContentSize().height -
			mscoreLabel->getContentSize().height - levelLabel->getContentSize().height + 3);
		getSprite()->addChild(levelLabel);
	}
}



int PlayerAttribute::mhp;
int PlayerAttribute::map;
int PlayerAttribute::mmoney;
int PlayerAttribute::damage;
int PlayerAttribute::shootSpeed;
int PlayerAttribute::mscore;
int PlayerAttribute::level;

char PlayerAttribute::heroName[10];