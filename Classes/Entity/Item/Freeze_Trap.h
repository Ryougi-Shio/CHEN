#pragma once
#include"Item.h"
//��������
class Freeze_Trap :public Item
{
public :
	virtual bool init();
	virtual void Interact(int mode);
	virtual void update(float dt);
	virtual void notice(char s[]);
	CREATE_FUNC(Freeze_Trap);
private:
	bool IsTrapping = 0;
};