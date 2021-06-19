#include "BossInterlude.h"
#include"Player.h"
#include"Monster.h"
#include"AllTag.h"
bool BossInterlude::init()
{
	return true;
}

void BossInterlude::playInterlude(Player* _player, Monster* _boss)
{
	auto visible = Director::getInstance()->getWinSize();
	Sprite* HeroSprite;
	Sprite* BossSprite;
	Label* HeroLabel;
	Label* BossLabel;
	Label* VSLabel = Label::createWithTTF("VS", "fonts/Marker Felt.ttf", 100);
	VSLabel->setPosition(visible.width / 2, visible.height / 2);
	VSLabel->setColor(Color3B(255, 0, 0));
	addChild(VSLabel,2);
	std::string s = _player->getHeroName();
	if (s =="knight")
	{
		HeroSprite = Sprite::create("background/knight.png");
		HeroLabel = Label::createWithTTF("knight", "fonts/Marker Felt.ttf", 75);
		HeroLabel->setColor(Color3B(255, 255, 0));
	}
	else if (s == "ranger")
	{
		HeroSprite = Sprite::create("background/Ranger.png");
		HeroLabel = Label::createWithTTF("ranger", "fonts/Marker Felt.ttf", 75);
		HeroLabel->setColor(Color3B(0, 191, 255));
	}
	switch (_boss->getTag())
	{
	case CthulhuEye_Monster_TAG:
		BossSprite = Sprite::create("background/CthulhuEye.png");
		BossLabel = Label::createWithTTF("Cthulhu's Eye", "fonts/Marker Felt.ttf", 75);
		BossLabel->setColor(Color3B(178,34,34));
		break;
	default:
		break;
	}
	addChild(HeroSprite,1);
	addChild(BossSprite,1);
	HeroSprite->addChild(HeroLabel, 1);
	BossSprite->addChild(BossLabel, 1);
	HeroLabel->setPosition(HeroSprite->getContentSize().width / 2, HeroSprite->getContentSize().height - HeroLabel->getContentSize().height);
	BossLabel->setPosition(BossSprite->getContentSize().width / 2, BossSprite->getContentSize().height - BossLabel->getContentSize().height);
	HeroSprite->setPosition(visible.width - HeroSprite->getContentSize().width / 2, HeroSprite->getContentSize().height / 2);
	BossSprite->setPosition(BossSprite->getContentSize().width / 2, BossSprite->getContentSize().height / 2);
	schedule(CC_SCHEDULE_SELECTOR(BossInterlude::remove), 5);
}

void BossInterlude::remove(float dt)
{
	Director::getInstance()->popScene();
}

