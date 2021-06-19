#pragma once
#include"Entity.h"
USING_NS_CC;
class Player;
class BattleMap;
class Item :public Entity
{
public:
	virtual bool init();
	virtual void Interact(int mode);//������Ʒ�Ľ�������
	virtual void update(float dt);
	virtual void notice(char s[]);//��ǩ��ʼ��
	void ChangeNotice(char s[]);
	void NoticeOnorOff(bool able);//��ǩ�Ƿ�ɼ�
	
	bool isAround(int Range);	//�жϳ����������Ƿ�����Χ
	bool getIsCanSee();			//0���ɼ���1�ɼ�
	bool getIsUsed();			//0�����ã�1����
	void setIsCanSee(bool can);
	void setIsUsed(bool used);
	void bindScene(Scene* scene);
	void bindMap(BattleMap* map);
	void bindPlayer(Player* player);

	CREATE_FUNC(Item);
protected:
	BattleMap* mMap;
	Scene* mScene;
	Player* mPlayer;
	Label* noticeLabel;	//��ǩ

	bool isCanSee = 0;
	bool isUsed=0;		//�Ƿ��ù�
	long startTime = 0;//���ڼ򵥵ļ�ʱ
};