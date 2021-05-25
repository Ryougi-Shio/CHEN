#include"cocos2d.h"
#include"StartScene.h"
#include"AudioEngine.h"
#include"OptionUI.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
/*初始界面的初始化
* 需包含：
* 背景界面以及标题的生成
* 开始游戏按键，设置按键，退出按键。
* 初始化背景音乐。
*/
bool StartScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	musicManager = musicManager->create();
	musicManager->startPlay("bgm/Title.mp3");

	//背景图片精灵
	auto backgroundSprite = Sprite::create("background/StartScene.png");
	backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2, origin.y + backgroundSprite->getContentSize().height / 2);
	this->addChild(backgroundSprite);

	//关闭按钮
	auto closeLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 75);
	auto closeItem = MenuItemLabel::create(closeLabel, CC_CALLBACK_1(StartScene::menuCloseCallBack, this));
	closeItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5, visibleSize.height / 2);

	//设置按钮
	auto setupLabel = Label::createWithTTF("Option", "fonts/Marker Felt.ttf", 75);
	auto setupItem = MenuItemLabel::create(setupLabel, CC_CALLBACK_1(StartScene::menuSetCallBack, this));
	setupItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5 - setupLabel->getContentSize().width * 2 , visibleSize.height / 2);

	//开始按钮
	auto startLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 75);
	auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(StartScene::menuStartCallBack, this));
	startItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5 - setupLabel->getContentSize().width * 1.5 -
							startLabel->getContentSize().width*3, visibleSize.height / 2);
	//菜单
	auto menu = Menu::create(closeItem,setupItem,startItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return 1;
}

void StartScene::menuStartCallBack(Ref* sender)
{
	musicManager->effectPlay("effect/button.mp3");
}

void StartScene::menuCloseCallBack(Ref* sender)
{
	musicManager->effectPlay("effect/button.mp3");
	Director::getInstance()->end();
}

void StartScene::menuSetCallBack(Ref* sender)
{
	musicManager->effectPlay("effect/button.mp3");
	MusicManager::menu(this);
	
}