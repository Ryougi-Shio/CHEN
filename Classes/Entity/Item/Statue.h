#pragma once
#include"Item.h"
class Statue :public Item
{
public:
	virtual bool init();
	virtual void Interact(int mode);
	virtual void update(float dt);
	virtual void notice(char s[]);
	void setType(int type);
	int getType();
	
	CREATE_FUNC(Statue);
private:
	int StatueType;
	//0 �˺�����
	//1 Ѫ���ָ�
	//2 ��Ǯ����
};