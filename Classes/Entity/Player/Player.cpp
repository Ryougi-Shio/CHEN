#include"Player.h"
#include"PlayerStates.h"
#include"Player/PlayerAttribute.h"
#include"PlayerTFSM/PlayerTFSM.h"
#include"Player/PlayerMove.h"
#include"Weapon/Pistol.h"
bool Player::init()
{
	if (weapon1!=nullptr)
	{
		weapon1->bindPlayer(this);
		this->addChild(weapon1, 2);
	}
	bindSprite(Sprite::create("Player/knight_rest1.png"));
	playerAttribute = PlayerAttribute::create();
	playerAttribute->retain();
	TFSM = PlayerTFSM::create();
	TFSM->retain();
	TFSM->bindPlayer(this);
	this->scheduleUpdate();//��������update����������
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//ÿ0.4f����һ��״̬�����º���
	PLAYERMOVE = PlayerMove::create();
	PLAYERMOVE->retain();
	PLAYERMOVE->bindPlayer(this);
	AnimateFrameCache_init();
	return 1;
}

PlayerAttribute* Player::getPlayerAttribute()
{
	return playerAttribute;
}

PlayerMove* Player::getplayermove()
{
	return PLAYERMOVE;
}
void Player::AnimateFrameCache_init()
{
	m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	m_frameCache->addSpriteFramesWithFile("Player/knight_animate.plist", "Player/knight_animate.png");//���֡�����ļ�������
}
void Player::rest()
{

	
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

	AnimationCache::destroyInstance();//����������


}
void Player::rest_flip()
{
	
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_rest%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	//animation->setLoops(-1);//-1��ʾ���޲���
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();

}
void Player::run()
{
	
	Vector<SpriteFrame*>frameArray;
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();
	
}
void Player::run_flip()
{
	
	Vector<SpriteFrame*>frameArray;
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "knight_move%d_flip.png", i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();
	//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();//������֡����

}


/*

* Ŀǰbug���������ӳ�
* Ŀǰ����
*/


void Player::TFSMupdate(float dt)
{
	TFSM->update(dt);
}

void Player::trueMouseMap(EventMouse::MouseButton key)
{
	mouseMap[key] = 1;
}

void Player::flaseMouseMap(EventMouse::MouseButton key)
{
	mouseMap[key] = 0;
}

void Player::update(float delta)//update for Player
{
	//Player�˶�

	PLAYERMOVE->Move();
	weapon1->update(delta);
	float x = mouseLocation.x;
	float y = mouseLocation.y;
//	pistol->getSprite()->setRotation(x);

	//CCLOG("%f,%f", x, y);
}
bool Player::getIsFlip()
{
	return PLAYERMOVE->getIsFlip();
}
std::map<EventMouse::MouseButton, bool> Player::getMouseMap()
{
	return mouseMap;
}
Weapon* Player::getWeapon1()
{
	return weapon1;
}
void Player::PistolInit()
{
	weapon1 = Pistol::create();
	weapon1->retain();
	weapon1->bindPlayer(this);
	weapon1->setPosition(getSprite()->getContentSize().width/2 , getContentSize().height / 2);
}

void Player::changeMouseLocation(Vec2 location)
{
	mouseLocation = location;
}

Vec2 Player::getMouseLocation()
{
	
	return mouseLocation;
}
Weapon* Player::weapon1;