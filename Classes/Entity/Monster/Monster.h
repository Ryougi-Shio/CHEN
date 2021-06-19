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

	void MoveUpdate(float dt);						//执行移动
	void ChangeFlipByDestination(Vec2 destination);//根据怪物移动的方向进行精灵翻转
	bool moveToDestination(Vec2 destination);

	void StrollAround();						//怪物小范围随意移动
	void ApproachPlayer(Vec2 playerDestination);//怪物向玩家方向靠近
	bool isAround();							//判断玩家是否在附近
	void bindScene(NormalBattleScene* scene);
	void takingDamage(int damage);				//怪物受到伤害
	bool CanReachto(int Mapx,int Mapy,bool isDip);//判断这里是不是墙壁
	void Birth(int i);							//怪物出生
	void reSetColor(float delay);				//颜色恢复
	

	void MonsterAnimate(char type[]);			//怪物动画

	void InitWithName(char s[]);			//根据名字进行初始化
	void dead();							//死亡动画
	void FramCacheInit(char Name[]);		

	void FlipUpdate(float dt);
	void TFSMupdate(float dt);
	void DeadUpdate(float dt);
	void BossDashUpdate(float dt);			//Boss冲刺
	void BossDashRecover(float dt);			//Boss冲刺暂停
	void setPhysicsBody(PhysicsBody* body);
	bool CanSee();
	bool getIsFlip();
	virtual bool init();
	virtual Ammo* MonsterAttack();			//怪物攻击
	int getHp();
	int getMaxHp();
	int getATK();
	bool getIsDead();
	PhysicsBody* getMyBody();
	friend class BattleScene;
	float Width;
	float Height;
	Ammo* ImmortalAmmo;
	void ImmortalAmmoUpdate(float dt);			//不灭子弹的位置更新
	void CallFellowMonsterUpdate(float dt);		//召唤眷属
	CREATE_FUNC( Monster);

protected:
	//怪物属性：
	/*血量
	* 最大血量
	* 攻击力
	*/
	int mHp;
	int MaxHp;
	int ATK;
	NormalBattleScene* mScene;
	MonsterTFSM* TFSM_M;
	/*怪物名字
	* 移动速度
	*/
	char MonsterName[30];
	double MonsterSpeed;
	bool isFlip=0;
	bool isdead = 0;

	PhysicsBody* PhysicsBody_M;
	SpriteFrameCache* m_frameCache;
};