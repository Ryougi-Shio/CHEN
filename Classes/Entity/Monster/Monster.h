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
//�������
class  Monster : public Entity
{
public:

	void MoveUpdate(float dt);						//ִ���ƶ�
	void ChangeFlipByDestination(Vec2 destination);//���ݹ����ƶ��ķ�����о��鷭ת
	bool moveToDestination(Vec2 destination);

	void StrollAround();						//����С��Χ�����ƶ�
	void ApproachPlayer(Vec2 playerDestination);//��������ҷ��򿿽�
	bool isAround();							//�ж�����Ƿ��ڸ���
	void bindScene(NormalBattleScene* scene);
	void takingDamage(int damage);				//�����ܵ��˺�
	bool CanReachto(int Mapx,int Mapy,bool isDip);//�ж������ǲ���ǽ��
	void Birth(int i);							//�������
	void reSetColor(float delay);				//��ɫ�ָ�
	

	void MonsterAnimate(char type[]);			//���ﶯ��

	void InitWithName(char s[]);			//�������ֽ��г�ʼ��
	void dead();							//��������
	void FramCacheInit(char Name[]);		

	void FlipUpdate(float dt);
	void TFSMupdate(float dt);
	void DeadUpdate(float dt);
	void BossDashUpdate(float dt);			//Boss���
	void BossDashRecover(float dt);			//Boss�����ͣ
	void setPhysicsBody(PhysicsBody* body);
	bool CanSee();
	bool getIsFlip();
	virtual bool init();
	virtual Ammo* MonsterAttack();			//���﹥��
	int getHp();
	int getMaxHp();
	int getATK();
	bool getIsDead();
	PhysicsBody* getMyBody();
	friend class BattleScene;
	float Width;
	float Height;
	Ammo* ImmortalAmmo;
	void ImmortalAmmoUpdate(float dt);			//�����ӵ���λ�ø���
	void CallFellowMonsterUpdate(float dt);		//�ٻ�����
	CREATE_FUNC( Monster);

protected:
	//�������ԣ�
	/*Ѫ��
	* ���Ѫ��
	* ������
	*/
	int mHp;
	int MaxHp;
	int ATK;
	NormalBattleScene* mScene;
	MonsterTFSM* TFSM_M;
	/*��������
	* �ƶ��ٶ�
	*/
	char MonsterName[30];
	double MonsterSpeed;
	bool isFlip=0;
	bool isdead = 0;

	PhysicsBody* PhysicsBody_M;
	SpriteFrameCache* m_frameCache;
};