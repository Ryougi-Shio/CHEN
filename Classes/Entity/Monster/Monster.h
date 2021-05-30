#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#define NORMAL 50
class NormalScene;
class MonsterTFSM;
class BattleScene;
USING_NS_CC;
//怪物基类
class  Monster : public Entity
{
public:

	void MoveUpdate(float dt);

	void move();//怪物实质移动
	void StrollAround();//怪物小范围随意移动
	void ApproachPlayer();//怪物向玩家方向靠近
	bool isAround();//判断玩家是否在附近
	void bindScene(NormalScene* scene);
	void takingDamage(int damage);//怪物受到伤害
	bool isWall(float x,float y);//判断这里是不是墙壁
	void Birth(const std::string place_name);

	
	virtual void rest();
	virtual void rest_flip();
	virtual void run();
	virtual void run_flip();
	virtual void dead();
	virtual void dead_flip();
	
	void TFSMupdate(float dt);


	friend class BattleScene;

	CREATE_FUNC( Monster);

protected:
	int mHp;
	NormalScene* mScene;
	MonsterTFSM* TFSM_M;
	float movespeedX;
	float movespeedY;
	float Speed=NORMAL;
	bool isFlip=0;
	SpriteFrameCache* m_frameCache;

};