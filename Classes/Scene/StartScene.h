#pragma once
#include "cocos2d.h"
#include"music.h"
USING_NS_CC;
/*初始场景类
* 需包含：
* 1：背景画面，游戏标题UI
* 2：设置按键以及设置界面
* 3：退出按键
*/
class StartScene : public Scene
{
public:
	virtual bool init() override;//初始化函数
	//virtual void update(float delat) override;//更新函数
	void menuCloseCallBack(Ref* sender);//关闭按钮回调
	void menuSetCallBack(Ref* sender);//设置按钮回调
	void menuStartCallBack(Ref* sender);//开始按钮回调
	//virtual void update(float delta);//更新函数
	CREATE_FUNC(StartScene);
private:
	MusicManager* musicManager;
	int backgroundAudio;
};