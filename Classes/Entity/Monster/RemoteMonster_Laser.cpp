#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"RemoteMonster_Laser.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
#include"Laser.h"
#include"json.h"

bool RemoteMonster_Laser::init()
{
	return 1;
}


Ammo* RemoteMonster_Laser::MonsterAttack()
{
	return Laser::create();
}
