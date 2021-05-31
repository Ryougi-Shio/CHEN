#pragma once
#include"cocos2d.h"
#define NORMAL 2
class Player;
USING_NS_CC;
/*
* ������ҵ��ƶ������һ��Player
* �����к��ƶ���صĶ�����������
*/
class PlayerMove:public Node
{
public:
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
	bool getIsFlip();
	//�жϴ���������ڵ�ͼ�϶�Ӧ�ĵ��ǲ���ǽ��

	bool isWall(float Px, float Py);
	void bindMap(TMXTiledMap* aMap);
	void TrueKeyCode(EventKeyboard::KeyCode keycode);
	void FalseKeyCode(EventKeyboard::KeyCode keycode);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> getkeyMap();
	Player* getPlayer();

	CREATE_FUNC(PlayerMove);
private:
	Player* mPlayer;	//PlayerMove���Player
	TMXTiledMap* map;	//PlayerMove��ĵ�ͼ
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;//���������״̬������Ϊtrue
	float movespeedX, movespeedY;
	float Speed = NORMAL;//�ٶȺ궨��ɵ�
	bool ismoveX=0;
	bool ismoveY=0;
	bool isFlip = 0;//��¼�Ƿ�ת�����ﳯ����Ϊ0�����ﳯ����Ϊ1
};