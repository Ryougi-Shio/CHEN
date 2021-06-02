#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#define NORMAL 35
class NormalScene;
class MonsterTFSM;
class BattleScene;
class NormalBattleScene;
class MonsterPistolAmmo;
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
	void bindScene(NormalBattleScene* scene);
	void takingDamage(int damage);//怪物受到伤害
	bool isWall(float x,float y);//判断这里是不是墙壁
	void Birth(const std::string place_name);

	
	virtual void rest();

	virtual void run();

	virtual void dead();

	void FlipUpdate(float dt);
	void TFSMupdate(float dt);
	void DeadUpdate(float dt);//检测死亡
	bool getIsDead();
	friend class BattleScene;
	virtual MonsterPistolAmmo* MonsterAttack();
	CREATE_FUNC( Monster);

protected:
	int mHp;
	NormalBattleScene* mScene;
	MonsterTFSM* TFSM_M;
	float movespeedX;
	float movespeedY;
	float Speed=NORMAL;
	bool isFlip=0;
	bool isdead = 0;
	SpriteFrameCache* m_frameCache;

};