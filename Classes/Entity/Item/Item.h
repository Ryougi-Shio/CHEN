#pragma once
#include"Entity.h"
USING_NS_CC;
class Player;
class BattleMap;
class Item :public Entity
{
public:
	virtual bool init();
	virtual void Interact(int mode);//各种物品的交互功能
	virtual void update(float dt);
	virtual void notice(char s[]);//标签初始化
	void ChangeNotice(char s[]);
	void NoticeOnorOff(bool able);//标签是否可见
	
	bool isAround(int Range);	//判断场景里的玩家是否在周围
	bool getIsCanSee();			//0不可见，1可见
	bool getIsUsed();			//0不可用，1可用
	void setIsCanSee(bool can);
	void setIsUsed(bool used);
	void bindScene(Scene* scene);
	void bindMap(BattleMap* map);
	void bindPlayer(Player* player);

	CREATE_FUNC(Item);
protected:
	BattleMap* mMap;
	Scene* mScene;
	Player* mPlayer;
	Label* noticeLabel;	//标签

	bool isCanSee = 0;
	bool isUsed=0;		//是否用过
	long startTime = 0;//用于简单的计时
};