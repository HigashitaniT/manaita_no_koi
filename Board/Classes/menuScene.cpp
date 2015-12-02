#include "menuScene.h"
#include "Recipe3.h"


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
		"START",
	};
	for (int i = 0; i < 1; i++)
	{
		makeButton(i + 10, name[i],ccp(480, 300 - 60 * i));
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
	default:
		return;
	}
	pScene = CCTransitionFade::create(0.5f, nextScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
}



