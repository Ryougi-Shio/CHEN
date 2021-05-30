#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 

#define RANGE 250
#define WIDTH 46
#define HEIGHTH 48
USING_NS_CC;

void  Monster::Birth(const std::string place_name)
{
	//对象层的使用
	TMXObjectGroup* objGroup = mScene->getMap()->getObjectGroup("Monster");//获取对象层
	auto MonsterBirth = objGroup->getObject(place_name);//获取对象
	getSprite()->setPosition(Vec2(MonsterBirth.at("x").asFloat(), MonsterBirth.at("y").asFloat()));//出生位置设置
}


bool  Monster::isAround()
{
	float Px = mScene->getPlayer()->getPositionX();
	float Py = mScene->getPlayer()->getPositionY();
	float Mx = getSprite()->getPositionX();
	float My = getSprite()->getPositionY();
	if (Px >= Mx - RANGE && Px <= Mx + RANGE && Py >= My - RANGE && Py <= My + RANGE)
		return true;
	else
		return false;
}
void  Monster::bindScene(NormalScene* scene)
{
	mScene = scene;
}
void  Monster::takingDamage(int damage)
{
	mHp -= damage;
}
void  Monster::move()
{
	bool canMove = 1;
	float Mx = getSprite()->getPositionX();
	float My = getSprite()->getPositionY();
	//CCLOG("Monster:(%f,%f)", Mx, My);

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
		this->getSprite()->runAction(move);//进行实质移动

	
}
void  Monster::StrollAround()
{
	srand((unsigned)time(NULL));
	int x = rand() %3 -1;//-1,0,1
	int y = rand() % 3 - 1;

	movespeedX = x*Speed;
	movespeedY = y *Speed ;
	//CCLOG("(%d,%d)", x, y);
	//CCLOG("Speed:(%f,%f)\n", movespeedX, movespeedY);
}
void  Monster::ApproachPlayer()
{
	float Px = mScene->getPlayer()->getPositionX();
	float Py = mScene->getPlayer()->getPositionY();
	float Mx = getSprite()->getPositionX();
	float My = getSprite()->getPositionY();
	if (Mx < Px)
		movespeedX = Speed;
	else
		movespeedX = -Speed;
	if (My < Py)
		movespeedY = Speed;
	else
		movespeedY = -Speed;
}
bool  Monster::isWall(float x,float y)
{

	int mapX = (int)(x/ 64);
	int mapY = (int)(12 - y/ 64);

	int tileGid = mScene->getMap()->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));

	if (tileGid)
	{
		return true;//是墙
	}

	else
	{
		return false; //不是墙
	}
}
void Monster::rest()
{
	;
}
void Monster::rest_flip()
{
	;
}void Monster::run()
{
	;
}
void Monster::run_flip()
{
	;
}
void Monster::dead()
{
	;
}
void Monster::dead_flip()
{
	;
}
void  Monster::	MoveUpdate(float dt)
{
	if (isAround())
	{
		ApproachPlayer();
	}
	else
	{
		StrollAround();
	}
	move();
	if (movespeedX > 0)
	{
		TFSM_M->changeState(new RunState_M());//改变状态机
		isFlip = 0;

	}
	if (movespeedX < 0)
	{
		TFSM_M->changeState(new RunState_Flip_M());
		isFlip = 1;
	}

	if ((!movespeedX) && (!movespeedY))
	{
		if (!isFlip)
			TFSM_M->changeState(new RestState_M());
		else
			TFSM_M->changeState(new RestState_Flip_M());
	}
	if (movespeedY)
	{
		if (!isFlip)
			TFSM_M->changeState(new RunState_M());
		else
			TFSM_M->changeState(new RunState_Flip_M());
	}
}
void Monster::TFSMupdate(float dt)
{
	TFSM_M->update(dt);
	if (mHp <= 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::MoveUpdate));
		this->unschedule(CC_SCHEDULE_SELECTOR(Monster::TFSMupdate));
		if (!isFlip)
			dead();
		else
			dead_flip();
	}
}