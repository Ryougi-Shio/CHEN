#pragma once
#include"Monster.h"
/*
* ����
* ��ʵ������ʵ��
*/
class State_M
{
public:
	virtual void execute(Monster* monster) = 0;
private:	

};