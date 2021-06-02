#include"MonsterStates.h"
#include"Monster.h"
USING_NS_CC;
void RunState_M::execute(Monster*monster)
{
	monster->run();
}

void RestState_M::execute(Monster*monster)
{
	monster->rest();
}
