#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#define NORMAL 35
#include"AllTag.h"
class NormalScene;
class MonsterTFSM;
class BattleScene;
class NormalBattleScene;
class MonsterPistolAmmo;
class Ammo;
USING_NS_CC;
//怪物基类
class  Monster : public Entity
{
public:

	void MoveUpdate(float dt);
	void ChangeFlipByDestination(Vec2 destination);
	bool moveToDestination(Vec2 destination);
//	void move();//怪物实质移动
	void StrollAround();//怪物小范围随意移动
	void ApproachPlayer(Vec2 playerDestination);//怪物向玩家方向靠近
	bool isAround();//判断玩家是否在附近
	void bindScene(NormalBattleScene* scene);
	void takingDamage(int damage);//怪物受到伤害
	bool CanReachto(int Mapx,int Mapy,bool isDip);//判断这里是不是墙壁
	void Birth(int i);
	void reSetColor(float delay);
	

	void MonsterAnimate(char type[]);

	void InitWithName(char s[]);
	void dead();
	void FramCacheInit(char Name[]);

	void FlipUpdate(float dt);
	void TFSMupdate(float dt);
	void DeadUpdate(float dt);//检测死亡
	void setPhysicsBody(PhysicsBody* body);
	bool CanSee();

	virtual bool init();
	virtual Ammo* MonsterAttack();

	bool getIsDead();
	PhysicsBody* getMyBody();
	friend class BattleScene;
	float Width;
	float Height;
	CREATE_FUNC( Monster);

protected:

	int mHp;
	NormalBattleScene* mScene;
	MonsterTFSM* TFSM_M;
	char MonsterName[30];
	double MonsterSpeed;
	bool isFlip=0;
	bool isdead = 0;

	PhysicsBody* PhysicsBody_M;
	SpriteFrameCache* m_frameCache;
};