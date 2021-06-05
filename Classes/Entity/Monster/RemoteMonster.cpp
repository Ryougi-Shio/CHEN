#include"Monster.h"
#include"NormalScene.h"
#include"MonsterStates.h"
#include"MonsterTFSM.h"
#include"RemoteMonster.h"
#include"Player.h"
#include <stdlib.h>
#include <time.h> 
#include"MonsterPistolAmmo.h"
#include"json.h"

bool RemoteMonster::init()
{
	return 1;
}

Ammo* RemoteMonster::MonsterAttack()
{
	return MonsterPistolAmmo::create();
}
