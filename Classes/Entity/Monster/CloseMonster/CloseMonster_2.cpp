#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"CloseMonster_2.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
bool CloseMonster_2::init()
{
	bindSprite(Sprite::create("Monster/pig_monster1.png"));
	mHp = 5;

	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	//TFSM->schedule(CC_SCHEDULE_SELECTOR(MonsterTFSM::update), 0.4f);
	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Monster/pig_monster_animate.plist", "Monster/pig_monster_animate.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.5f);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数

	return 1;
}
void CloseMonster_2::dead()
{
	;
}
void CloseMonster_2::dead_flip()
{
	;
}
void CloseMonster_2::rest()
{
	;
}
void CloseMonster_2::rest_flip()
{
	;
}
void CloseMonster_2::run()
{


	Vector<SpriteFrame*>frameArray;
	for (int i = 2	; i <= 5; i++)
	{
		char s[50];
		sprintf(s, "pig_monster%d.png", i);
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
void CloseMonster_2::run_flip()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 2; i <= 5; i++)
	{
		char s[50];
		sprintf(s, "pig_monster%d_flip.png", i);
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