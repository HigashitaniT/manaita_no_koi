#include "menuScene.h"
#include "Recipe3.h"
#include "Recipe4.h"
#include "Recipe5.h"
#include "Recipe7.h"
#include "Recipe8.h"
#include "Recipe9.h"
#include "Recipe12.h"
#include "Recipe13.h"
#include "Recipe14.h"
#include "Recipe26.h"
#include "TimerTest.h"

USING_NS_CC;

CCScene* menuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	menuScene *layer = menuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool menuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	char* name[] =
	{
		"Recipe 3",
		"Recipe 4",
		"Recipe 5",
		"Recipe 7",
		"Recipe 8",
		"Timer Test !",
		"Recipe 9",
		"Recipe 12",
		"Recipe 13",
		"Recipe 14",
		"Recipe 26",
	};
	for (int i = 0; i < 11; i++)
	{
		makeButton(i + 10, name[i],
			ccp(250 + (i / 10) * 460, 600 - 60 * (i % 10)));
	}

    return true;
}


void menuScene::makeButton(int tag, char* msg, CCPoint pos)
{
	CCRect spriteRect = CCRectMake(0, 0, 80, 80);
	CCRect capInsents = CCRectMake(12, 12, 56, 56);
	CCScale9Sprite* pSprite =
		CCScale9Sprite::create("button9.png",
		spriteRect,
		capInsents);
	CCLabelTTF* label =
		CCLabelTTF::create(msg, "Arial", 30);
	CCControlButton* button =
		CCControlButton::create(label, pSprite);
	button->setPreferredSize(CCSizeMake(300, 50));
	button->setPosition(pos);
	this->addChild(button, 1, tag);
	button->addTargetWithActionForControlEvents(this,
		cccontrol_selector(menuScene::tapCallback),
		CCControlEventTouchUpInside);
}

void menuScene::tapCallback(CCObject* pSender, CCControlEvent event)
{
	CCSprite* btn = (CCSprite*)pSender;
	int tag = btn->getTag();
	CCScene* nextScene;
	CCScene* pScene;
	switch (tag)
	{
	case 10:
		nextScene = Recipe3Scene::scene();
		break;
	case 11:
		nextScene = Recipe4Scene::scene();
		break;
	case 12:
		nextScene = Recipe5Scene::scene();
		break;
	case 13:
		nextScene = Recipe7Scene::scene();
		break;
	case 14:
		nextScene = Recipe8Scene::scene();
		break;
	case 15:
		nextScene = TimerTestScene::scene();
		break;
	case 16:
		nextScene = Recipe9Scene::scene();
		break;
	case 17:
		nextScene = Recipe12Scene::scene();
		break;
	case 18:
		nextScene = Recipe13Scene::scene();
		break;
	case 19:
		nextScene = Recipe14Scene::scene();
		break;
	case 20:
		nextScene = Recipe26Scene::scene();
		break;
	default:
		return;
	}
	pScene = CCTransitionFade::create(0.5f, nextScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
}



