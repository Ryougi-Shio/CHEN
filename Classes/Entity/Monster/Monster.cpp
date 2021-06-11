#include"Monster.h"
#include"NormalBattleScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
#include"Map/BattleMap.h"
#include"MonsterPistolAmmo.h"
#include"json.h"
#define RANGE 400

USING_NS_CC;

bool Monster::init()
{
	return 1;
}
void  Monster::Birth(int i)
{	
	//对象层的使用
	TMXObjectGroup* objGroup = mScene->getParentMap()->getBattleMap()->getObjectGroup("Monster");//获取对象层
	auto s = new char[40];
	sprintf(s,"Monster_birth%d", i);
	auto MonsterBirth = objGroup->getObject(s);//获取对象
	getSprite()->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height / 2);
	setPosition(Vec2(MonsterBirth.at("x").asFloat(), MonsterBirth.at("y").asFloat()));//出生位置设置
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::FlipUpdate), 0.01f);
	delete s;
	Width = this->getSprite()->getContentSize().width;
	Height = this->getSprite()->getContentSize().height;



}

void Monster::reSetColor(float delay)
{
	getSprite()->setColor(Color3B(255, 255, 255));
}


bool  Monster::isAround()
{
	float Px = mScene->getPlayer()->getPositionX();
	float Py = mScene->getPlayer()->getPositionY();
	float Mx = getPositionX();
	float My = getPositionY();
	if (Px >= Mx - RANGE && Px <= Mx + RANGE && Py >= My - RANGE && Py <= My + RANGE)
		return true;
	else
		return false;
}
bool Monster::getIsDead()
{
	return isdead;
}
void  Monster::bindScene(NormalBattleScene* scene)
{
	mScene = scene;
}
void  Monster::takingDamage(int damage)
{
	getSprite()->setColor(Color3B(255, 0, 0));
	mHp -= damage;
	scheduleOnce(CC_SCHEDULE_SELECTOR(Monster::reSetColor), 0.1f);
}
/*
void  Monster::move()
{
	bool canMove = 1;
	float Mx = getPositionX();
	float My = getPositionY();
	int mapX = (int)(Mx / 64);
	int mapY = (int)(11 - int(My / 64));
	

	auto move = MoveBy::create(0.5, Vec2(movespeedX, movespeedY));
	if (movespeedX > 0)
	{
		if (isWall(Mx + WIDTH , My))
			canMove = 0;
	}
	if (movespeedX < 0)
	{
		if (isWall(Mx - WIDTH , My))
			canMove = 0;
	}
	if (movespeedY > 0)
	{
		if (isWall(Mx , My+HEIGHTH))
			canMove = 0;
	}
	if (movespeedY < 0)
	{
		if (isWall(Mx, My-HEIGHTH))
			canMove = 0;
	}
	if(canMove)
		this->runAction(move);//进行实质移动

	
}*/
void  Monster::StrollAround()
{

	float Mx = getPositionX();
	float My = getPositionY();
	int ix = rand() % 64 * (rand() % 3 - 1);
	int iy = rand() % 64 * (rand() % 3 - 1);
	Vec2 Destination;
	Destination = Vec2(Mx + ix, My + iy);
	while (!moveToDestination(Destination))
	{
		ix = rand() % 64 * (rand() % 3 - 1);
		iy = rand() % 64 * (rand() % 3 - 1);
		Destination = Vec2(Mx + ix, My + iy);
	}


}

bool  Monster::CanReachto(int Mapx, int Mapy,bool isDip=0)
{

	

	int tileGid = mScene->getParentMap()->getBattleMap()->getLayer("wall")->getTileGIDAt(Vec2(Mapx, Mapy));
	if (!isDip)//非斜向判断
	{
		if (tileGid)
		{
			return true;// 不能走
		}

		else
		{
			return false; //能走
		}
	}
	else//斜向判断
	{
		if (tileGid)
		{
			return true;// 是墙不能走
		}
		else
		{

				int ix = int(getPositionX() / 64) - Mapx;
				int iy = 11 - int(getPositionY() / 64) - Mapy;
				int tiledGidx = mScene->getParentMap()->getBattleMap()->getLayer("wall")->getTileGIDAt(Vec2(Mapx + ix, Mapy));
				int tiledGidy = mScene->getParentMap()->getBattleMap()->getLayer("wall")->getTileGIDAt(Vec2(Mapx, Mapy + iy));
				if (!tiledGidx || !tiledGidy)
				{
					return false;//能走
				}
				else
				{
					return true;
				}

			
		}
	}
}

void Monster::setPhysicsBody(PhysicsBody* body)
{
	PhysicsBody_M = body;
}
PhysicsBody* Monster::getMyBody()
{
	return PhysicsBody_M;
}
void Monster::DeadUpdate(float dt)
{
	if (mHp <= 0)
	{

		this->removeAllComponents();
		this->stopAllActions();
		dead();
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate));
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate));

	}

}

void  Monster::	MoveUpdate(float dt)
{
	
	if (CanSee())
		ApproachPlayer(mScene->getPlayer()->getPosition());
	else
		StrollAround();

}
bool Monster::CanSee()
{
	float Px = mScene->getPlayer()->getPositionX();
	float Py = mScene->getPlayer()->getPositionY();
	float Mx = getPositionX();
	float My = getPositionY();
	int Map_Px = Px / 64;
	int Map_Py = int(11 - int(Py / 64));
	int Map_Mx = Mx / 64;
	int Map_My = int(11 - int(My / 64));
	int ix = Map_Mx > Map_Px ? -1 : 1;
	int iy = Map_My > Map_Py ? -1 : 1;
	if (Map_Mx == Map_Px)
		ix = 0;
	if (Map_My == Map_Py)
		iy = 0;
	if (Map_Mx == Map_Px)
	{
		for (int i =MIN(Map_My,Map_Py); i < MAX(Map_My, Map_Py); i++)
		{
			if (CanReachto(Map_Mx, i))
				return false;

		}
		return true;
	}
	else if (Map_My == Map_Py)
	{
		for (int i = MIN(Map_Mx, Map_Px); i < MAX(Map_Mx, Map_Px); i++)
		{
			if (CanReachto(i, Map_My))
				return false;

		}
		return true;
	}
	else
	{
		for (Vec2 i =Vec2(Map_Mx,Map_My);;)
		{
			if (i.x != Map_Px && i.y != Map_Py)
			{
				i += Vec2(ix, iy);
				if (CanReachto(i.x, i.y, 1))
					return false;
			}
			else if (i.x != Map_Px || i.y != Map_Py)
			{
				ix = int(i.x) == Map_Px ? 0 : ix;
				iy = int(i.y) == Map_Py ? 0 : iy;
				i += Vec2(ix, iy);
				if (CanReachto(i.x,i.y))
				{
					return false;
				}
			}
			else
			{
				break;
			}
		}
		return true;

	}
}
void Monster::TFSMupdate(float dt)
{
	TFSM_M->update(dt);
	if (mHp <= 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate));
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate));
		dead();

	}
}
void Monster::FlipUpdate(float dt)
{
	if (isFlip)
		this->getSprite()->setFlippedX(1);
	else
		this->getSprite()->setFlippedX(0);
}
Ammo* Monster::MonsterAttack()
{
	return MonsterPistolAmmo::create();
}
void Monster::ChangeFlipByDestination(Vec2 destination)
{
	float Mx = getPositionX();
	float My = getPositionY();
	if (Mx <= destination.x)
		isFlip = 0;
	else
		isFlip = 1;
//	CCLOG("%d", isFlip);
}
bool Monster::moveToDestination(Vec2 destination)
{
	
	int map_X = destination.x / 64;
	int map_Y = 11-int(destination.y / 64);
	if (CanReachto(map_X,map_Y))
	{
		return false;
	}
	int map_Mx = getPositionX() / 64;
	int map_My = 11 - int(getPositionY() / 64);
	int ix = map_Mx > map_X ? -1 : 1;
	int iy = map_My > map_Y ? -1 : 1;
	if (map_Mx == map_X)
		ix = 0;
	if (map_My == map_Y)
		iy = 0;
	int Length = MIN(abs(map_X- map_Mx),abs( map_Y - map_My));
	if (abs(map_Mx-map_X)<=1 && abs(map_My - map_Y) <= 1)
	{
		//map_X = (int(destination.x) + ix * getSprite()->getContentSize().width / 2)/64;
		//map_Y = 11 - int((int(destination.y) + iy * getSprite()->getContentSize().height / 2) / 64);
		if (map_X == map_Mx || map_Y == map_My)
		{
			int i = destination.x+getSprite()->getContentSize().width;
			int y = destination.y + getSprite()->getContentSize().height;
			//CCLOG("%d,,,%d", int(((destination.x + getSprite()->getContentSize().width) / 64)), 11 - int(((destination.y + getSprite()->getContentSize().height) / 64)));
			if (CanReachto((destination.x + getSprite()->getContentSize().width) / 64, map_Y) || CanReachto(map_X, 11 - int(((destination.y + getSprite()->getContentSize().height) / 64))))
			{
				return false;
			}
			MoveTo* moveTo = MoveTo::create(MonsterSpeed, destination);
			this->runAction(moveTo);

			//动画
			TFSM_M->changeState(new RunState_M());
			ChangeFlipByDestination(destination);

			return true;
		}
		else
		{
			int i = destination.x;
			int y = destination.y;
//			CCLOG("%d,,,%d", int(((destination.x + getSprite()->getContentSize().width) / 64)), 11 - int(((destination.y + getSprite()->getContentSize().height) / 64)));
			if (CanReachto((destination.x + getSprite()->getContentSize().width) / 64, 11 - int((destination.y + getSprite()->getContentSize().height) / 64), 1))
			{
				return false;
			}
			MoveTo* moveTo = MoveTo::create(MonsterSpeed, destination);
			this->runAction(moveTo);
			TFSM_M->changeState(new RunState_M());
			return true;
		}
	}
	else
	{
		CCLOG("too far");
		return false;
	}
	/*else
	{
		Vec2 destination_temp1= Vec2(map_Mx + ix * Length, 11-map_My + iy * Length) * 64;
		MoveTo* moveTo_dip = MoveTo::create(1.0f*1.41*Length, destination_temp1);
		this->runAction(moveTo_dip);
		if (map_Mx + ix * Length == map_X && map_My + iy * Length == map_Y)
			return true;
		else if (map_Mx + ix * Length == map_X)
		{
			MoveTo* moveTo_dire = MoveTo::create(1.0f * abs(map_My + iy - map_Y), destination);
			runAction(moveTo_dire);
		}
		else if (map_My + iy * Length == map_Y)
		{
			MoveTo* moveTo_dire = MoveTo::create(1.0f * abs(map_Mx + ix - map_X), destination);
			runAction(moveTo_dire);
		}
		else
			CCLOG("Unexpected Error");
		return true;
	}*/
	
	/*
	int map_X = destination.x / 64;
	int map_Y = 11 - int(destination.y / 64);
	int map_Mx = getPositionX() / 64;
	int map_My = 11 - int(getPositionY() / 64);
	int ix = map_Mx > map_X ? -1 : 1;
	int iy = map_My > map_Y ? -1 : 1;
	if (map_Mx == map_X)
		ix = 0;
	if (map_My == map_Y)
		iy = 0;
	//修正
//	map_X = (destination.x+ix * Width*0.5)/64;
//	map_Y = 11-int(destination.y+iy * Height*0.5)/64;
	int Length = MIN(abs(map_X - map_Mx), abs(map_Y - map_My));
	if (abs(map_Mx - map_X) <= 1 && abs(map_My - map_Y) <= 1)
	{
		if (map_X == map_Mx || map_Y == map_My)
		{
			if (CanReachto(map_X, map_Y))
			{
				return false;
			}
			MoveTo* moveTo = MoveTo::create(1.0f, destination);
			this->runAction(moveTo);
			return true;
		}
		else
		{
			if (CanReachto(map_X  , map_Y , 1))
			{
				return false;
			}
			MoveTo* moveTo = MoveTo::create(1.0f, destination);
			this->runAction(moveTo);
			return true;
		}
	}
	else
	{
		Vec2 destination_temp1 = Vec2(map_Mx + ix * Length, map_My + iy * Length) * 64;
		MoveTo* moveTo_dip = MoveTo::create(1.0f * 1.41 * Length, destination_temp1);
		this->runAction(moveTo_dip);
		if (map_Mx + ix * Length == map_X && map_My + iy * Length == map_Y)
			return true;
		else if (map_Mx + ix * Length == map_X)
		{
			MoveTo* moveTo_dire = MoveTo::create(1.0f * abs(map_My + iy - map_Y), destination);
		}
		else if (map_My + iy * Length == map_Y)
		{
			MoveTo* moveTo_dire = MoveTo::create(1.0f * abs(map_Mx + ix - map_X), destination);
		}
		else
			CCLOG("Unexpected Error");
		return true;
	}*/
}

void  Monster::ApproachPlayer(Vec2 playerDestination)
{
	int map_X = playerDestination.x / 64;
	int map_Y = 11 - int(playerDestination.y / 64);
	int map_Mx = getPositionX() / 64;
	int map_My = 11 - int(getPositionY() / 64);
	int ix = map_Mx > map_X ? -1 : 1;
	int iy = map_My > map_Y ? -1 : 1;
	float Mx = getPositionX();
	float My = getPositionY();
	if (map_Mx == map_X)
		ix = 0;
	if (map_My == map_Y)
		iy = 0;
	Vec2 Destination;
	if (!ix || !iy)
	{
		Destination = Vec2(Mx + ix * 64, My - iy *64);
		moveToDestination(Destination);
	}
	else
	{
		Destination = Vec2(Mx + ix * (rand() % 64), My - iy * (rand() % 64));
		if (!moveToDestination(Destination))
		{
			if (rand()%2)//优先X轴
			{
				Destination = Vec2(Mx + ix * (rand() % 64), My);
				if (!moveToDestination(Destination))
				{
					Destination = Vec2(Mx, My - iy * (rand() % 64));
					if (!moveToDestination(Destination))
					{
						StrollAround();
					}
				}
			}
			else
			{
				Destination = Vec2(Mx, My - iy * (rand() % 64));
				if (!moveToDestination(Destination))
				{
					Destination = Vec2(Mx + ix * (rand() % 64), My);
					if (!moveToDestination(Destination))
					{
						StrollAround();
					}
				}
			}
		}
	}
}



void Monster::InitWithName(char s[])
{

	//血量读取
	strcpy(MonsterName, s);


	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("json/Monster.json");
	if (reader.parse(data, root, false) == true)
	{
		mHp = root[MonsterName]["Hp"].asInt();
	}

	//移动速度读取
	Json::Reader reader_speed;
	Json::Value root_speed;



	if (reader_speed.parse(data, root_speed, false) == true)
	{
		MonsterSpeed = root_speed[MonsterName]["MoveSpeed"].asDouble();
	}

	char s_Rest[50];
	sprintf(s_Rest, "Monster/%s_rest1.png", MonsterName);

	bindSprite(Sprite::create(s_Rest));


	TFSM_M = MonsterTFSM::create();
	TFSM_M->retain();
	TFSM_M->bindMonster(this);
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate), MonsterSpeed);//每0.5f调用一次运动更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate), 0.4f);//每0.4f调用一次状态机更新函数
	this->schedule(CC_SCHEDULE_SELECTOR(Monster::DeadUpdate), 0.01f);
}
void Monster::FramCacheInit(char Name[])
{
	char s_Plist[50], s_Plist_Png[50];
	sprintf(s_Plist, "Monster/%s_animate.plist", Name);
	sprintf(s_Plist_Png, "Monster/%s_animate.png", Name);

	m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile(s_Plist, s_Plist_Png);
}

void Monster::dead()
{
	isdead = 1;
	Vector<SpriteFrame*>frameArray;
	char s[50];
	sprintf(s, "%s_dead.png", MonsterName);
	auto frame1 = m_frameCache->getSpriteFrameByName(s);
	frameArray.pushBack(frame1);


	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);
	AnimationCache::destroyInstance();
}

void Monster::MonsterAnimate(char type[])
{
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "%s_%s%d.png", MonsterName, type, i);
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
