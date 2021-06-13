#include"Player.h"
#include"PlayerStates.h"
#include"Player/PlayerAttribute.h"
#include"PlayerTFSM/PlayerTFSM.h"
#include"Player/PlayerMove.h"
#include"Weapon/Pistol.h"
#include"Weapon/Sword.h"
#include"Weapon/PitchFork.h"
#include"Weapon/Shotgun.h"
#include"music.h"
#include"AllTag.h"

bool Player::init()
{
	if (strlen(heroName) == 0)
	{
		changeHero("ranger");
	}
	if (weapon1!=nullptr)
	{
		weapon1->removeFromParentAndCleanup(0);
		weapon1->bindPlayer(this);
		this->addChild(weapon1, 3);
	}
	if (weapon2!=nullptr)
	{
		weapon2->removeFromParentAndCleanup(0);
		weapon2->bindPlayer(this);
	}
	{
		char s[40];
		sprintf(s, "Player/%s_rest1.png", heroName);
		bindSprite(Sprite::create(s));
	}
	playerAttribute = PlayerAttribute::create();
	playerAttribute->retain();
	playerAttribute->bindPlayer(this);
	this->addChild(playerAttribute->getSkillEffect(), -2);
	this->addChild(playerAttribute->getBuffEffect(), -1);
	TFSM = PlayerTFSM::create();
	TFSM->retain();
	TFSM->bindPlayer(this);
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Player::FlipUpdate), 0.01f);
	this->schedule(CC_SCHEDULE_SELECTOR(Player::SkillUpdate),0.01f);
//	this->schedule(CC_SCHEDULE_SELECTOR(PlayerMove::FlipToMouse),0.01f);
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
	m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	char plist[40],png[40];
	sprintf(plist, "Player/%s_animate.plist", heroName);
	sprintf(png, "Player/%s_animate.png", heroName);
	m_frameCache->addSpriteFramesWithFile(plist, png);//添加帧动画文件到缓存
}

void Player::HeroSkill(int mode)
{

	std::string s= this->getHeroName();
	if ((!SkillIson||clock()-skillTime>500)&&s=="knight")//CD:0.5s
	{
		playerAttribute->changeDamage_Buff(5);
		playerAttribute->changeShootSpeed_Buff(250);
		playerAttribute->getSkillEffect()->setOpacity(255);
		skillTime = clock();
		SkillIson = 1;
	}
	if ((!SkillIson || clock() - skillTime > 2000) && s== "ranger")//CD2s
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate));
		skill_ranger();
		skillTime = clock();


		this->removeComponent(this->getPhysicsBody());
		SkillIson = 1;
	}
}

void Player::SkillUpdate(float dt)
{
	std::string s = this->getHeroName();
	if (clock() - skillTime > 1000&&SkillIson && s == "knight")//持续1s
	{
		playerAttribute->changeDamage_Buff(-5);
		playerAttribute->changeShootSpeed_Buff(-250);
		playerAttribute->getSkillEffect()->setOpacity(0);
		SkillIson=0;
	}
	if (SkillIson&& s == "ranger")
	{

		if (this->getPhysicsBody()==nullptr&&(clock() - skillTime > 1200))//持续1.2s
		{
			this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);
			auto physicsBody = PhysicsBody::createBox(Size(40.0f, 40.0f),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			this->addComponent(physicsBody);
			this->getPhysicsBody()->setCategoryBitmask(0x0010);
			this->getPhysicsBody()->setCollisionBitmask(0x0010);
			this->getPhysicsBody()->setContactTestBitmask(0x0010);
			this->schedule(CC_SCHEDULE_SELECTOR(Player::TFSMupdate), 0.4f);
		}
		if (clock() - skillTime > 2000)//CD2s
		{
			
			SkillIson = 0;
		}
//			
	}
}
void Player::skill_ranger()
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_skill%d.png", heroName, i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_skill%d.png", heroName, i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(2);
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();
	
}
void Player::rest()
{

	
	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_rest%d.png",heroName,i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}

	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	//animation->setLoops(-1);//-1表示无限播放
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);

	AnimationCache::destroyInstance();//清理动画缓存


}

void Player::run()
{
	
	Vector<SpriteFrame*>frameArray;
	for (int i = 2; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_move%d.png",heroName,i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
	AnimationCache::destroyInstance();
	
}

void Player::dead()
{
	Vector<SpriteFrame*>frameArray;
	auto frameCache= SpriteFrameCache::getInstance();
	{
		char plist[40], png[40];
		sprintf(plist, "Player/%s_animate.plist", heroName);
		sprintf(png, "Player/%s_animate.png", heroName);
		frameCache->addSpriteFramesWithFile(plist, png);
	}
	char frame[40];
	sprintf(frame, "%s_down.png", heroName);
	auto frame1 =frameCache->getSpriteFrameByName(frame);
	frameArray.pushBack(frame1);


	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	AnimationCache::destroyInstance();
}

/*

* 目前bug：
* 目前需求：
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
	//Player运动

	PLAYERMOVE->Move();
	if(weapon1)
		weapon1->update(delta);
	//if (weapon2)
		//weapon2->update(delta);
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
Weapon* Player::getWeapon2()
{
	return weapon2;
}
void Player::swapWeapon()
{
	auto temp = weapon2;
	weapon1->removeFromParentAndCleanup(0);
	weapon2 = weapon1;
	weapon1 = temp;
	addChild(weapon1);
}
void Player::PitchForkInit()
{
	if (!weapon1)
	{
		weapon1 = PitchFork::create();
		weapon1->retain();
		weapon1->bindPlayer(this);
		weapon1->setPosition(getSprite()->getContentSize().width / 2 + 5, 0);
		this->addChild(weapon1, 2);
	}
	else if (!weapon2)
	{
		weapon2 = PitchFork::create();
		weapon2->retain();
		weapon2->bindPlayer(this);
		weapon2->setPosition(getSprite()->getContentSize().width / 2, 0);
	}
}
void Player::ShotgunInit()
{
	if (!weapon1)
	{
		weapon1 = Shotgun::create();
		weapon1->retain();
		weapon1->bindPlayer(this);
		weapon1->setPosition(getSprite()->getContentSize().width / 2 + 5, 0);
		this->addChild(weapon1, 2);
	}
	else if (!weapon2)
	{
		weapon2 = Shotgun::create();
		weapon2->retain();
		weapon2->bindPlayer(this);
		weapon2->setPosition(getSprite()->getContentSize().width / 2, 0);
	}
}
void Player::SwordInit()
{
	if (!weapon1)
	{
		weapon1 = Sword::create();
		weapon1->retain();
		weapon1->bindPlayer(this);
		weapon1->setPosition(getSprite()->getContentSize().width / 2+5 ,-20 );
		this->addChild(weapon1,2);
	}
	else if(!weapon2)
	{
		weapon2 = Sword::create();
		weapon2->retain();
		weapon2->bindPlayer(this);
		weapon2->setPosition(getSprite()->getContentSize().width / 2 , 0);
	}
}
void Player::PistolInit()
{
	
	if (!weapon1)
	{
		weapon1 = Pistol::create();
		weapon1->retain();
		weapon1->bindPlayer(this);
		weapon1->setPosition(getSprite()->getContentSize().width / 2, 0);
		this->addChild(weapon1);
	}
	else
	{
		weapon2 = Pistol::create();
		weapon2->retain();
		weapon2->bindPlayer(this);
		weapon2->setPosition(getSprite()->getContentSize().width / 2 , 0);

	}
}
void Player::changeMouseLocation(Vec2 location)
{
	mouseLocation = location;
}

Vec2 Player::getMouseLocation()
{
	
	return mouseLocation;
}
void Player::deadNotice()
{
	
}
void Player::changeHero(char hero[])
{
	strcpy(heroName, hero);

	playerAttribute->changeHero(hero);
	AnimateFrameCache_init();
	
}
char* Player::getHeroName()
{
	return heroName;
}
void Player::FlipUpdate(float dt)//翻转
{
	PLAYERMOVE->FlipToMouse();
	if (getIsFlip() == 0)
		this->getSprite()->setFlippedX(0);
	else
		this->getSprite()->setFlippedX(1);
}
void Player::pickWeapon(int TAG)
{

	weapon1->removeFromParentAndCleanup(0);
	weapon2 = weapon1;
	weapon1 = nullptr;
	switch (TAG)
	{
	case AllTag::PlayerWeapon_Sword_TAG:
		SwordInit();
		break;
	case AllTag::PlayerWeapon_Pistol_TAG:
		PistolInit();
		break;
	case AllTag::PlayerWeapn_PitchFork_TAG:
		PitchForkInit();
		break;
	case AllTag::PlayerWeapon_Shotgun_TAG:
		ShotgunInit();
		break;
	default:
		break;
	}
}



Weapon* Player::weapon1;
Weapon* Player::weapon2;
char Player::heroName[10];