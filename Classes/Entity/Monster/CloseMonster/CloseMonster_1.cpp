#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"CloseMonster_1.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
#include"MonsterPistolAmmo.h"
#include"json.h"
bool CloseMonster_1::init()
{
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("json/Monster.json");
	if (reader.parse(data, root, false) == true)
	{
		//CCLOG("%d", root.isMember("knight"));
		//if (strlen(heroName) == 0)
		//{
			//changeHero("knight");
		//}
		mHp = root["small_monster"]["Hp"].asInt();
		//maxAp = root[heroName]["Ap"].asInt();
	}
	bindSprite(Sprite::create("Monster/O_small_monster_move4.png"));
	//mHp = 5;

	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	//TFSM->schedule(CC_SCHEDULE_SELECTOR(MonsterTFSM::update), 0.4f);
	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Monster/O_small_monster_animate.plist", "Monster/O_small_monster_animate.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.5f);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::DeadUpdate), 0.01f);
	return 1;
}
MonsterPistolAmmo* CloseMonster_1::MonsterAttack()
{
	return MonsterPistolAmmo::create();
}
void CloseMonster_1::dead()
{
	isdead = 1;
	Vector<SpriteFrame*>frameArray;

	auto frame1 = m_frameCache->getSpriteFrameByName("O_small_monster_dead.png");
	frameArray.pushBack(frame1);


	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}

void CloseMonster_1::rest()
{
	;
}

void CloseMonster_1::run()
{


	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "O_small_monster_move%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
	//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();



}
