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
	this->scheduleUpdate();//��������update����������
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//ÿ0.4f����һ��״̬�����º���
	PLAYERMOVE = PlayerMove::create();
	PLAYERMOVE->retain();
	PLAYERMOVE->bindPlayer(this);
	return 1;
}

void Player::rest()
{

	auto m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//����֡�����ļ�������
	Vector<SpriteFrame*>frameArray;//�������б���
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_rest%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//��֡���뵽������
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//��������
	//animation->setLoops(-1);//-1��ʾ���޲���
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ�ļ��ʱ��
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();//������������
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//��������֡����

}
void Player::rest_flip()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//����֡�����ļ�������
	Vector<SpriteFrame*>frameArray;//�������б���
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_rest%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//��֡���뵽������
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//��������
	//animation->setLoops(-1);//-1��ʾ���޲���
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ�ļ��ʱ��
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();//������������
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//��������֡����
}
void Player::run()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//����֡�����ļ�������
	Vector<SpriteFrame*>frameArray;//�������б���
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//��֡���뵽������
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//��������
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ�ļ��ʱ��
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();//������������
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//��������֡����
}
void Player::run_flip()
{
	auto m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//����֡�����ļ�������
	Vector<SpriteFrame*>frameArray;//�������б���
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//��֡���뵽������
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//��������
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ�ļ��ʱ��
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();//������������
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//��������֡����

}

/*
* ����ƶ�ԭ����
* keyMap�������룬�簴��Wʱ����W������true���ɿ�W����W������false������keyMap�м����״̬�����ƶ�
* �ƶ��󣬽��ƶ��ٶ���0
* Ŀǰbug��
* Ŀǰ���󣺱߽��ж��Լ���ͷ�ƶ����Լ�����״̬�����л���
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

std::map<cocos2d::EventKeyboard::KeyCode, bool> Player::getkeyMap()//��ȡkeyMap
{
	return keyMap;
}
float Player::getSpeed()
{
	return Speed;
}
void Player::TrueKeyCode(EventKeyboard::KeyCode keycode)//���̰��£���Ӧkeycode��true
{
	keyMap[keycode] = true;
}
void Player::FalseKeyCode(EventKeyboard::KeyCode keycode)//�����ɿ�����Ӧkeycode��false
{
	keyMap[keycode] = false;
}
void Player::bindMap(TMXTiledMap* aMap)
{
	map = aMap;
}
bool Player::isWall(float Px, float Py)//�жϴ����������꣬�ڵ�ͼ�϶�Ӧ�ĵط��ǲ���ǽ
{
	int mapX = (int)(Px / 64);
	int mapY = (int)(12 - Py / 64);
	CCLOG("X:%d    Y:%d", mapX, mapY);
	int tileGid = map->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
	//CCLOG("%d", tileGid);
	if (tileGid)
	{
		//CCLOG("TTTTTTTTTTTTTTTTTTT");��ǽ��������
		return false;
	}

	else
	{
		//CCLOG("FFFFFFFFFFFFFFFFFFF");����ǽ������
		return true;
	}
}
void Player::update(float delta)//update for Player
{
	//Player�˶�
	PLAYERMOVE->Move();

}