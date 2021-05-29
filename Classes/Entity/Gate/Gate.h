#pragma once
#include"Entity.h"
class Player;
class NormalScene;
USING_NS_CC;
/*
*Gate������
* ��ҿ�����ʱ������Ӧ
* ��ʾ��E���д���
* 
*/
class Gate :public Entity
{
public:
	virtual bool init();
	virtual void update(float delta);
	bool isAround(float Px,float Py);//�������Ƿ�������Χ
	//void transferMenu();//���Ͳ˵���ʾ���ں�������ť
	void bindPlayer(Player* mPlayer);
	void bindStart(NormalScene* mScene);
	void bindDestination(NormalScene* mScene);
	void notice();
	NormalScene* getStart();
	NormalScene* getDestination();
	CREATE_FUNC(Gate);
private:
	Player* player;
	NormalScene* start;
	NormalScene* destination;
	Label* noticeLabel;
};