#include"MonsterStates.h"
#include"Monster.h"
USING_NS_CC;
void RunState_M::execute(Monster*monster)
{
	char s[10] = "move";
	
	monster->MonsterAnimate(s);
}

void RestState_M::execute(Monster*monster)
{
	char s[10] = "rest";

	monster->MonsterAnimate(s);
}
