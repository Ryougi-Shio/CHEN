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

	void run();//�ܲ���������
	void frozen();
	void skill_ranger();
	void TFSMupdate(float dt);//����״̬��ר��update��ÿ0.4fһ�ε���
	PlayerAttribute* getPlayerAttribute();
	PlayerMove* getplayermove();
	virtual void update(float delta);
	void AnimateFrameCache_init();
	void trueMouseMap(EventMouse::MouseButton key);
	void flaseMouseMap(EventMouse::MouseButton key);
	void PistolInit();
	void SwordInit();
	void PitchForkInit();
	void ShotgunInit();
	void changeMouseLocation(Vec2 location);
	Vec2 getMouseLocation();
	bool getIsFlip();
	void FlipUpdate(float dt);
	std::map<EventMouse::MouseButton, bool> getMouseMap();
	Weapon* getWeapon1();
	Weapon* getWeapon2();
	void swapWeapon();
	bool pickWeapon(int TAG);//����������TAGΪҪ���õ�����
	void dead();
	void deadNotice();
	void changeHero(char hero[]);
	char* getHeroName();
	void  HeroSkill(int mode);
	bool getIsdead();
	void SkillUpdate(float dt);
	void LevelUp();
	CREATE_FUNC(Player);
	friend class PlayerMove;
private:
	long skillTime = 0;
	 
	PlayerTFSM* TFSM;
	PlayerMove* PLAYERMOVE;
	PlayerAttribute* playerAttribute;
	SpriteFrameCache* m_frameCache;
	static Weapon* weapon1;
	static Weapon* weapon2;
	std::map<EventMouse::MouseButton, bool> mouseMap;
	Vec2 mouseLocation;
	int Skill_CD;
	int Skill_Lasting;
	bool SkillIson=0;
	bool isDead=false;
	static char heroName[10];
};
