#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
#define NORMAL 50
class NormalScene;
class MonsterTFSM;
class BattleScene;
USING_NS_CC;
//�������
class  Monster : public Entity
{
public:

	void MoveUpdate(float dt);

	void move();//����ʵ���ƶ�
	void StrollAround();//����С��Χ�����ƶ�
	void ApproachPlayer();//��������ҷ��򿿽�
	bool isAround();//�ж�����Ƿ��ڸ���
	void bindScene(NormalScene* scene);
	void takingDamage(int damage);//�����ܵ��˺�
	bool isWall(float x,float y);//�ж������ǲ���ǽ��
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