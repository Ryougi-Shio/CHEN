#include"PlayerStates.h"
#include"Entity/Player.h"
USING_NS_CC;
void RunState::execute(Player* player)
{
	;
}

void RestState::execute(Player* player)
{
	player->rest();
}