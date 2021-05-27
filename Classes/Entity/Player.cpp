#include"Player.h"
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
	m_frameCache->addSpriteFramesWithFile("Player/knight_rest.plist", "Player/knight_rest.png");//添加帧动画文件到缓存
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
}

/*
* 玩家移动原理：
* WS对应moveY,分别有判定是否在移动以及移动速度两个变量，AD同理对应moveX、
* 按下按键时，如果此时另一按键未按下，则将ismove置1，表明开始移动，并且设定对应的移动速度
* 松开时，将ismove与移动速度置0
* 目前bug：
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