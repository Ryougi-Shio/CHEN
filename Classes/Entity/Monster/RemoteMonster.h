#pragma once
#include"Monster.h"
#include"MonsterPistolAmmo.h"
/*远程怪物
* 根据读入的名字具体化
*/
class RemoteMonster :public Monster
{
public:
	virtual void MonsterAnimate(char type[]);
	virtual void dead();
	virtual void FramCacheInit(char Name[]);
	void InitWithName(char s[]);
	MonsterPistolAmmo* MonsterAttack();
	CREATE_FUNC(RemoteMonster);
private:
	char MonsterName[30];
	SpriteFrameCache* m_frameCache;
};