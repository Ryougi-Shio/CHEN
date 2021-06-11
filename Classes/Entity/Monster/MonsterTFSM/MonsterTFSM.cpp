#include"MonsterTFSM.h"
#include"MonsterStates.h"
#include"Monster.h"
bool MonsterTFSM::init()
{
	changeState(new RestState_M());//Ä¬ÈÏÐÝÏ¢×´Ì¬
	return 1;
}

void MonsterTFSM::changeState(State_M* state)
{
	mCurState = state;
}

void MonsterTFSM::bindMonster(Monster*monster)
{
	mmonster = monster;
}

void MonsterTFSM::update(float dt)
{

	mCurState->execute(mmonster);
	
}
State_M* MonsterTFSM::getmCurState()
{
	return mCurState;
}