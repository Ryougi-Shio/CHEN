#pragma once
#include"Entity.h"
#define NORMAL 2
class Weapon;
class PlayerAttribute;
class PlayerTFSM;
class PlayerMove;
USING_NS_CC;
/*
* �����
* ����
* ��ʼ��
* �ƶ�
* ����״̬����
* Ѫ�������ף���Ǯ����
*/
class Player : public Entity
{
public:
	virtual bool init();
	void rest();//������������
	void rest_flip();
	void run();//�ܲ���������
	void run_flip();
	void TFSMupdate(float dt);//����״̬��ר��update��ÿ0.4fһ�ε���
	PlayerAttribute* getPlayerAttribute();
	PlayerMove* getplayermove();
	virtual void update(float delta);
	void AnimateFrameCache_init();
	void trueMouseMap(EventMouse::MouseButton key);
	void flaseMouseMap(EventMouse::MouseButton key);
	void PistolInit();
	void changeMouseLocation(Vec2 location);
	Vec2 getMouseLocation();
	bool getIsFlip();
	std::map<EventMouse::MouseButton, bool> getMouseMap();
	Weapon* getWeapon1();
	CREATE_FUNC(Player);
	friend class PlayerMove;
private:
	PlayerTFSM* TFSM;
	PlayerMove* PLAYERMOVE;
	PlayerAttribute* playerAttribute;
	SpriteFrameCache* m_frameCache;

	static Weapon* weapon1;
	std::map<EventMouse::MouseButton, bool> mouseMap;
	Vec2 mouseLocation;
};
