#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"CloseMonster_4.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
bool CloseMonster_4::init()
{
	bindSprite(Sprite::create("Monster/Y_craw_monster1.png"));
	mHp = 5;

	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	//TFSM->schedule(CC_SCHEDULE_SELECTOR(MonsterTFSM::update), 0.4f);
	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Monster/Y_craw_monster_animate.plist", "Monster/Y_craw_monster_animate.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.5f);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数

	return 1;
}
void CloseMonster_4::dead()
{
	;
}
void CloseMonster_4::dead_flip()
{
	;
}
void CloseMonster_4::rest()
{
	Vector<SpriteFrame*>frameArray;

	auto frame1 = m_frameCache->getSpriteFrameByName("Y_craw_monster2.png");
	frameArray.pushBack(frame1);
	auto frame2 = m_frameCache->getSpriteFrameByName("Y_craw_monster6.png");
	frameArray.pushBack(frame2);

	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.2f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
	//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

}
void CloseMonster_4::rest_flip()
{
	Vector<SpriteFrame*>frameArray;

	auto frame1 = m_frameCache->getSpriteFrameByName("Y_craw_monster2_flip.png");
	frameArray.pushBack(frame1);
	auto frame2 = m_frameCache->getSpriteFrameByName("Y_craw_monster6_flip.png");
	frameArray.pushBack(frame2);

	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.2f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
	//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
}
void CloseMonster_4::run()
{


	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 5; i++)
	{
		char s[50];
		sprintf(s, "Y_craw_monster%d.png", i);
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
void CloseMonster_4::run_flip()
{

	Vector<SpriteFrame*>frameArray;
	for (int i = 2; i <= 5; i++)
	{
		char s[50];
		sprintf(s, "Y_craw_monster%d_flip.png", i);
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