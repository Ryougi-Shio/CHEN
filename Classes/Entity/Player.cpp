#include"Player.h"
bool Player::init()
{
	ismoveX = 0;
	ismoveY = 0;
	bindSprite(Sprite::create("Player/knight_rest1.png"));
	TFSM = PlayerTFSM::create();
	TFSM->retain();
	TFSM->bindPlayer(this);
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	return 1;
}
void Player::update(float dt)
{
	;
}
void Player::rest()
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Player/knight_rest1.png", Rect(0, 0, 52, 60)));
	animFrames.pushBack(SpriteFrame::create("Player/knight_rest2.png", Rect(0, 0, 52, 60)));
	animFrames.pushBack(SpriteFrame::create("Player/knight_rest3.png", Rect(0, 0, 52, 60)));
	animFrames.pushBack(SpriteFrame::create("Player/knight_rest4.png", Rect(0, 0, 52, 60)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	getSprite()->runAction(RepeatForever::create(animate));
}

/*
* 玩家移动原理：
* WS对应moveY,分别有判定是否在移动以及移动速度两个变量，AD同理对应moveX、
* 按下按键时，如果此时另一按键未按下，则将ismove置1，表明开始移动，并且设定对应的移动速度
* 松开时，将ismove与移动速度置0
* 目前bug：在按下W时按下S，人物会继续往上走(这里没问题)，但是在持续按住S的情况下松开W，人物会站在原地而不是往下走。AD的情况同理。
* 目前需求：边界判定以及镜头移动，以及动画状态机的切换。
*/
void Player::playerMove()
{
	auto move = MoveBy::create(0, Vec2(movespeedX, movespeedY));
	this->runAction(move);
}

void Player::TFSMupdate(float dt)
{
	TFSM->update(dt);
}

void Player::startmoveX(float x)
{
	movespeedX = x;
	ismoveX = 1;
}

void Player::startmoveY(float y)
{
	movespeedY = y;
	ismoveY = 1;
}

void Player::stopmoveX()
{
	movespeedX = 0;
	ismoveX = 0;
}

void Player::stopmoveY()
{
	movespeedY = 0;
	ismoveY = 0;
}

bool Player::getismoveX()
{
	return ismoveX;
}

bool Player::getismoveY()
{
	return ismoveY;
}

float Player::getspeedX()
{
	return movespeedX;
}

float Player::getspeedY()
{
	return movespeedY;
}
