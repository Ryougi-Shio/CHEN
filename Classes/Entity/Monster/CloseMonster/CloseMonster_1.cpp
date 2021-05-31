#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"CloseMonster_1.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
bool CloseMonster_1::init()
{
	bindSprite(Sprite::create("Monster/O_small_monster_move4.png"));
	mHp = 5;

	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	//TFSM->schedule(CC_SCHEDULE_SELECTOR(MonsterTFSM::update), 0.4f);
	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("Monster/O_small_monster_animate.plist", "Monster/O_small_monster_animate.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), 0.5f);//ÿ0.5f����һ���˶����º���
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//ÿ0.4f����һ��״̬�����º���

	return 1;
}
void CloseMonster_1::dead()
{
	Vector<SpriteFrame*>frameArray;

	auto frame1 = m_frameCache->getSpriteFrameByName("O_small_monster_move4.png");
	//frameArray.pushBack(frame1);
	auto frame2 = m_frameCache->getSpriteFrameByName("O_small_monster_dead.png");
	frameArray.pushBack(frame2);

	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.4f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}
void CloseMonster_1::dead_flip()
{
	Vector<SpriteFrame*>frameArray;

	auto frame1 = m_frameCache->getSpriteFrameByName("O_small_monster_move4_flip.png");
	//frameArray.pushBack(frame1);
	auto frame2 = m_frameCache->getSpriteFrameByName("O_small_monster_dead_flip.png");
	frameArray.pushBack(frame2);

	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.4f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}
void CloseMonster_1::rest()
{
	;
}
void CloseMonster_1::rest_flip()
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
void CloseMonster_1::run_flip()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "O_small_monster_move%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}