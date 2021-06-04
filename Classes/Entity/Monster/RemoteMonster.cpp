#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"RemoteMonster.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
#include"MonsterPistolAmmo.h"
#include"json.h"


void RemoteMonster::InitWithName(char s[])
{

	strcpy(MonsterName, s);
	char s_Json[50];
	sprintf(s_Json,"json/%s.json",MonsterName);
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile(s_Json);
	if (reader.parse(data, root, false) == true)
	{
		mHp = root[MonsterName]["Hp"].asInt();
	}


	char s_Rest[50];
	sprintf(s_Rest,"Monster/%s_rest1.png",MonsterName);

	bindSprite(Sprite::create(s_Rest));


	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.15f);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::DeadUpdate), 0.01f);
}
void RemoteMonster::FramCacheInit(char Name[])
{
	char s_Plist[50], s_Plist_Png[50];
	sprintf(s_Plist, "Monster/%s_animate.plist", Name);
	sprintf(s_Plist_Png, "Monster/%s_animate.png", Name);

	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile(s_Plist, s_Plist_Png);
}
MonsterPistolAmmo* RemoteMonster::MonsterAttack()
{
	return MonsterPistolAmmo::create();
}
void RemoteMonster::dead()
{
	isdead = 1;
	Vector<SpriteFrame*>frameArray;
	char s[50];
	sprintf(s,"%s_dead.png",MonsterName);
	auto frame1 = m_frameCache->getSpriteFrameByName(s);
	frameArray.pushBack(frame1);


	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);
	AnimationCache::destroyInstance();
}

void RemoteMonster::MonsterAnimate(char type[])
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "%s_%s%d.png", MonsterName,type, i);
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
