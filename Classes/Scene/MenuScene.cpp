#include"MenuScene.h"
#include"ui/CocosGUI.h"
#include"StartScene.h"
USING_NS_CC;
bool MenuScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
//	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	//renderTexture->begin();

	//Director::getInstance ()->getRunningScene()->visit();
//	renderTexture->end();
//	Sprite* back = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
//	back->setPosition(visibleSize/2);
//	back->setFlippedY(1);
	//back->setColor(Color3B(128, 138, 135));
//	this->addChild(back);


	//UI背景图片
	auto UIbackground = Sprite::create("UI/OptionUI.png");
	UIbackground->setPosition(visibleSize / 2);
	this->addChild(UIbackground, 5);

	//音乐音量滑动条文字
	auto musicLabel = Label::createWithTTF("setMusicVolume", "fonts/Marker Felt.ttf", 24);
	musicLabel->setPosition(UIbackground->getContentSize().width / 2, UIbackground->getContentSize().height - musicLabel->getContentSize().height * 4);
	UIbackground->addChild(musicLabel);

	//音乐音量滑动条
	auto musicSlider = cocos2d::ui::Slider::create();
	musicSlider->loadBarTexture("UI/sliderTrack.png");
	musicSlider->loadSlidBallTextures("UI/sliderThumb.png");
	musicSlider->loadProgressBarTexture("UI/sliderProgress.png");
	musicSlider->setPercent(MusicManager::getMusicVolume() * 100);
	musicSlider->setPosition(Vec2(UIbackground->getContentSize().width / 2, UIbackground->getContentSize().height -
		musicLabel->getContentSize().height * 4 - musicSlider->getContentSize().height * 2));
	musicSlider->addEventListener([&](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
			int percent = slider->getPercent();
			int maxPercent = slider->getMaxPercent();
			MusicManager::setMusicVolume(1.0f * percent / maxPercent) ;
			AudioEngine::setVolume(MusicManager::getBgm(), MusicManager::getMusicVolume());
			break;
		}
		default:
			break;
		}
		});
	UIbackground->addChild(musicSlider);

	//音效音量滑动条文字
	auto effectLabel = Label::createWithTTF("setEffectVolume", "fonts/Marker Felt.ttf", 24);
	effectLabel->setPosition(UIbackground->getContentSize().width / 2, UIbackground->getContentSize().height -
		musicLabel->getContentSize().height * 4 - effectLabel->getContentSize().height * 4);
	UIbackground->addChild(effectLabel);

	//音效音量滑动条
	auto effectSlider = cocos2d::ui::Slider::create();
	effectSlider->loadBarTexture("UI/sliderTrack.png");
	effectSlider->loadSlidBallTextures("UI/sliderThumb.png");
	effectSlider->loadProgressBarTexture("UI/sliderProgress.png");
	effectSlider->setPercent(MusicManager:: getEffectVolume()* 100);
	effectSlider->setPosition(Vec2(UIbackground->getContentSize().width / 2, UIbackground->getContentSize().height -
		musicLabel->getContentSize().height * 4 - effectLabel->getContentSize().height * 4 - effectSlider->getContentSize().height * 2));
	effectSlider->addEventListener([&](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
			int percent = slider->getPercent();
			int maxPercent = slider->getMaxPercent();

			MusicManager::setEffectVolume(1.0f * percent / maxPercent);
			AudioEngine::setVolume(MusicManager::getEffect(), MusicManager::getEffectVolume());
			break;
		}
		default:
			break;
		}
		});
	UIbackground->addChild(effectSlider);

	//退出游戏

	auto closeGameLable = Label::createWithTTF("Exit Game", "fonts/Marker Felt.ttf", 48);
	auto closeGameItem = MenuItemLabel::create(closeGameLable, [=](Ref* sender) {
		MusicManager::effectPlay("effect/button.mp3");
		Director::getInstance()->end();
		});
	closeGameItem->setPosition(UIbackground->getContentSize().width / 2, closeGameItem->getContentSize().height * 2);

	//退出设置
	auto closeLabel = Label::createWithTTF("Return", "fonts/Marker Felt.ttf", 48);
	auto closeItem = MenuItemLabel::create(closeLabel, [=](Ref* sender) {
		MusicManager::effectPlay("effect/button.mp3");
		Director::getInstance()->popScene();
		});
	closeItem->setPosition(UIbackground->getContentSize().width / 2, closeItem->getContentSize().height * 2 + closeGameItem->getContentSize().height * 2);

	//返回开始场景
	auto homeLabel = Label::createWithTTF("Home", "fonts/Marker Felt.ttf", 48);
	auto homeItem = MenuItemLabel::create(homeLabel, [=](Ref* sender) {
		MusicManager::effectPlay("effect/button.mp3");
		Director::getInstance()->replaceScene(StartScene::create());
		});
	homeItem->setPosition(UIbackground->getContentSize().width / 2, closeItem->getContentSize().height * 2 + closeGameItem->getContentSize().height * 2 + homeItem->getContentSize().height * 1.5);


	auto optionUI = Menu::create(closeGameItem, closeItem, homeItem, nullptr);
	optionUI->setPosition(Vec2::ZERO);
	UIbackground->addChild(optionUI);
	
	return 1;
}
