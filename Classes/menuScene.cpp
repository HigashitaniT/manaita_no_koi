#include "menuScene.h"
#include "HelloWorldScene.h"
/*#include "Recipe3.h"
#include "Recipe4.h"
#include "Recipe5.h"
#include "Recipe7.h"
#include "Recipe8.h"
*/
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
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	char* titleName[] =
	{
		"recipe 3",
		"recipe 4",
		"recipe 5",
		"recipe 7",
		"recipe 8",
	};

	for (int i = 0; i < 5; i++)
	{
		MakeButton(titleName[i], i + 10, ccp(250, 600 - 60 * i));
	}
	return true;
}

void menuScene::tapCallback(CCObject* pSender, CCControlEvent event)
{

	CCSprite* spr = (CCSprite*)pSender;
	int tag = spr->getTag();
	CCScene* nextScene = NULL;
	switch (tag)
	{
	case    10:
		nextScene = Recipe3Scene::scene();
		break;
	case    11:
		nextScene = Recipe4Scene::scene();
		break;
	case    12:
		nextScene = Recipe5Scene::scene();
		break;
	case    13:
		nextScene = Recipe7Scene::scene();
		break;
	case    14:
		nextScene = Recipe8Scene::scene();
		break;

	default:
		break;
	}
	CCScene* pScene = CCTransitionCrossFade::create(0.5f, nextScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
	CCLOG("kita:%d",tag);
}

void menuScene::MakeButton(char* name, int num, CCPoint pos)
{

	CCRect spriteRect = CCRectMake(0, 0, 80, 80);
	CCRect capInsents = CCRectMake(12, 12, 56, 56);
	CCScale9Sprite*backgroundSprite =
		CCScale9Sprite::create("button9.png", spriteRect, capInsents);

	CCLabelTTF* label = CCLabelTTF::create(name, "Arial", 30);
	CCControlButton* button =
		CCControlButton::create(label, backgroundSprite);

	button->setPreferredSize(CCSizeMake(300, 50));
	button->setPosition(pos);
	this->addChild(button,1,num);

	button->addTargetWithActionForControlEvents(this,
		cccontrol_selector(menuScene::tapCallback),
		CCControlEventTouchUpInside);
}