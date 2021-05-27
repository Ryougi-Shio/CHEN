#include"Player.h"
#include"PlayerStates.h"
bool Player::init()
{
	ismoveX = 0;
	ismoveY = 0;
	bindSprite(Sprite::create("Player/knight_rest1.png"));
	TFSM = PlayerTFSM::create();
	TFSM->retain();
	TFSM->bindPlayer(this);
	this->scheduleUpdate();//开启调用update函数的能力
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	return 1;
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
* 玩家移动原理：
* keyMap存贮键码，如按下W时，将W键码置true，松开W，将W键码置false，根据keyMap中键码的状态进行移动
* 移动后，将移动速度置0
* 目前bug：
* 目前需求：边界判定以及镜头移动，以及动画状态机的切换。
*/

void Player::playerMove()
{
	auto move = MoveBy::create(0, Vec2(movespeedX, movespeedY));
	this->runAction(move);

	
	if (movespeedX > 0)
	{
		TFSM->changeState(new RunState());
		isFlip = 0;

	}
	if (movespeedX < 0)
	{
		TFSM->changeState(new RunState_Flip());
		isFlip = 1;
	}
	
	if ((!movespeedX) && (!movespeedY))
	{
		if(!isFlip)
			TFSM->changeState(new RestState());
		else
			TFSM->changeState(new RestState_Flip());
	}
	if (movespeedY)
	{
		if(!isFlip)
			TFSM->changeState(new RunState());
		else
			TFSM->changeState(new RunState_Flip());
	}
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

std::map<cocos2d::EventKeyboard::KeyCode, bool> Player::getkeyMap()//获取keyMap
{
	return keyMap;
}

void Player::TrueKeyCode(EventKeyboard::KeyCode keycode)//键盘按下，对应keycode置true
{
	keyMap[keycode] = true;
}
void Player::FalseKeyCode(EventKeyboard::KeyCode keycode)//键盘松开，对应keycode置false
{
	keyMap[keycode] = false;
}

void Player::update(float delta)//update for Player
{
	//Player运动
	auto right = (EventKeyboard::KeyCode)127;
	auto left = (EventKeyboard::KeyCode)124;
	auto up = (EventKeyboard::KeyCode)146;
	auto down = (EventKeyboard::KeyCode)142;
	if (keyMap[up])
	{
		startmoveY(Speed);
	}
	if (keyMap[down])
	{
		startmoveY(-Speed);
	}
	if (keyMap[left])
	{
		startmoveX(-Speed);
	}
	if (keyMap[right])
	{
		startmoveX(Speed);
	}
	if (keyMap[right] && keyMap[up])
	{
		startmoveX(Speed);
		startmoveY(Speed);
	}
	if (keyMap[left] && keyMap[up])
	{
		startmoveX(-Speed);
		startmoveY(Speed);
	}
	if (keyMap[left] && keyMap[down])
	{
		startmoveX(-Speed);
		startmoveY(-Speed);
	}
	if (keyMap[right] && keyMap[down])
	{
		startmoveX(Speed);
		startmoveY(-Speed);
	}
	playerMove();
	stopmoveX();
	stopmoveY();

}