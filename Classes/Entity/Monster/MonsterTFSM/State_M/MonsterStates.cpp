#include"MonsterStates.h"
#include"Monster.h"
USING_NS_CC;
void RunState_M::execute(Monster*monster)
{
	monster->run();
}
void RunState_Flip_M::execute(Monster*monster)
{
	monster->run_flip();
}
void RestState_M::execute(Monster*monster)
{
	monster->rest();
}
void RestState_Flip_M::execute(Monster*monster)
{
	monster->rest_flip();
}