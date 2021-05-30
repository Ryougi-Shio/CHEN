#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"CloseMonster_3.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
bool CloseMonster_3::init()
{
	bindSprite(Sprite::create("Monster/snow_monster_stay1.png"));
	mHp = 5;

	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	//TFSM->schedule(CC_SCHEDULE_SELECTOR(MonsterTFSM::update), 0.4f);
	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Monster/snow_monster_animate.plist", "Monster/snow_monster_animate.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.5f);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数

	return 1;
}
void CloseMonster_3::dead()
{
	;
}
void CloseMonster_3::dead_flip()
{
	;
}
void CloseMonster_3::rest()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "snow_monster_stay%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}
void CloseMonster_3::rest_flip()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "snow_monster_stay%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}
void CloseMonster_3::run()
{


	Vector<SpriteFrame*>frameArray;
	for (int i = 1	; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "snow_monster_move%d.png", i);
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
void CloseMonster_3::run_flip()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "snow_monster_move%d_flip.png", i);
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