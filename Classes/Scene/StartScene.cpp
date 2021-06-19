#include"cocos2d.h"
#include"StartScene.h"
#include"AudioEngine.h"
#include"ui/CocosGUI.h"
#include"SafeScene.h"
USING_NS_CC;
/*��ʼ����ĳ�ʼ��
* �������
* ���������Լ����������
* ��ʼ��Ϸ���������ð������˳�������
* ��ʼ���������֡�
*/
bool StartScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	if (AudioEngine::getPlayingAudioCount() == NULL)
	{
		musicManager = musicManager->create();
		musicManager->startPlay("bgm/Title.mp3");
	}
	else
		musicManager->changeMusic("bgm/Title.mp3");

	//����ͼƬ����
	auto backgroundSprite = Sprite::create("background/StartScene.png");
	backgroundSprite->setPosition(origin.x + backgroundSprite->getContentSize().width / 2, origin.y + backgroundSprite->getContentSize().height / 2);
	this->addChild(backgroundSprite);

	//�رհ�ť
	auto closeLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 75);
	auto closeItem = MenuItemLabel::create(closeLabel, CC_CALLBACK_1(StartScene::menuCloseCallBack, this));
	closeItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5, visibleSize.height / 2);

	//���ð�ť
	auto setupLabel = Label::createWithTTF("Option", "fonts/Marker Felt.ttf", 75);
	auto setupItem = MenuItemLabel::create(setupLabel, CC_CALLBACK_1(StartScene::menuSetCallBack, this));
	setupItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5 - setupLabel->getContentSize().width * 2 , visibleSize.height / 2);

	//��ʼ��ť
	auto startLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 75);
	auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(StartScene::menuStartCallBack, this));
	startItem->setPosition(visibleSize.width - closeLabel->getContentSize().width * 1.5 - setupLabel->getContentSize().width * 1.5 -
							startLabel->getContentSize().width*3, visibleSize.height / 2);
	//�˵�
	auto menu = Menu::create(closeItem,setupItem,startItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return 1;
}

void StartScene::menuStartCallBack(Ref* sender)
{
	musicManager->effectPlay("effect/button.mp3");
	Director::getInstance()->replaceScene(SafeScene::create());
	//Director::getInstance()->replaceScene(BattleScene::create());
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