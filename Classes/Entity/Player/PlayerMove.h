#pragma once
#include"cocos2d.h"
#define NORMAL 4
class Player;
USING_NS_CC;
/*
* ������ҵ��ƶ������һ��Player
* �����к��ƶ���صĶ�����������
*/
class PlayerMove:public Node
{
public:
	virtual bool init();
	void bindPlayer(Player* player);//�����
	void Move();//�����ƶ��ĺ���
	void playerMove();//����runAction���ı�״̬���ĺ���
	void startmoveX(float x);//�ı�X������ٶ�
	void startmoveY(float y);//�ı�Y������ٶ�
	void stopmoveX();
	void stopmoveY();
	bool getismoveX();
	bool getismoveY();
	float getspeedX();
	float getspeedY();
	float getSpeed();
	void setSpeed(float s);
	bool getIsFlip();

	
	void setSpeed(int spee);
	bool isWall(float Px, float Py);//�жϴ���������ڵ�ͼ�϶�Ӧ�ĵ��ǲ���ǽ��
	void bindMap(TMXTiledMap* aMap);
	void TrueKeyCode(EventKeyboard::KeyCode keycode);
	void FalseKeyCode(EventKeyboard::KeyCode keycode);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> getkeyMap();
	void FlipToMouse();
	Player* getPlayer();
	bool getIsFrozen();
	void setFrozen(bool frozen);
	void FrozenUpdate(float dt);
	CREATE_FUNC(PlayerMove);
private:
	Player* mPlayer;	//PlayerMove���Player
	TMXTiledMap* map;	//PlayerMove��ĵ�ͼ
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;//���������״̬������Ϊtrue
	float movespeedX, movespeedY;
	float Speed = NORMAL;//�ٶȺ궨��,�ɵ�
	bool ismoveX=0;
	bool ismoveY=0;
	bool isFlip = 0;//��¼�Ƿ�ת�����ﳯ����Ϊ0�����ﳯ����Ϊ1
	bool isFrozen=false;
};