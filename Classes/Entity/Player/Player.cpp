#include"Player.h"
#include"PlayerStates.h"
bool Player::init()
{

	bindSprite(Sprite::create("Player/knight_rest1.png"));
	TFSM = PlayerTFSM::create();
	TFSM->retain();
	TFSM->bindPlayer(this);
	this->scheduleUpdate();//开启调用update函数的能力
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	PLAYERMOVE = PlayerMove::create();
	PLAYERMOVE->retain();
	PLAYERMOVE->bindPlayer(this);
	return 1;
}
PlayerMove* Player::getplayermove()
{
	return PLAYERMOVE;
}
void Player::rest()
{

	auto m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//添加帧动画文件到缓存
	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_rest%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	//animation->setLoops(-1);//-1表示无限播放
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();//清理动画缓存
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//清理精灵帧缓存

}
void Player::rest_flip()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//添加帧动画文件到缓存
	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_rest%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	//animation->setLoops(-1);//-1表示无限播放
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();//清理动画缓存
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//清理精灵帧缓存
}
void Player::run()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//添加帧动画文件到缓存
	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();//清理动画缓存
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//清理精灵帧缓存
}
void Player::run_flip()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//添加帧动画文件到缓存
	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();//清理动画缓存
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//清理精灵帧缓存

}

/*

* 目前bug：动画有延迟
* 目前需求：玩家UI，学习json如何使用。
*/


void Player::TFSMupdate(float dt)
{
	TFSM->update(dt);
}



void Player::update(float delta)//update for Player
{
	//Player运动
	PLAYERMOVE->Move();
}