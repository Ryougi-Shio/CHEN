#pragma once
#include"Item.h"
#include"cocos2d.h"
//�ر���
USING_NS_CC;
class TreasureBoxes :public Item
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(char s[]);
	virtual void notice(char s[]);
	bool getIsOpen();//0�رգ�1��
	void BoxBirth(int i);
	CREATE_FUNC(TreasureBoxes);
private:
	bool isOpen = 0;


};