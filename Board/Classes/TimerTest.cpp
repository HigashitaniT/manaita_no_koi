#include "TimerTest.h"

USING_NS_CC;

CCScene* TimerTestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	TimerTestScene *layer = TimerTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TimerTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	timer = 0;
	CCString* str = CCString::createWithFormat("%02d:%02d:%02d", timer/3600, (timer % 3600) / 60, timer % 60);
	CCLabelTTF* timerLabel = CCLabelTTF::create(str->getCString(), "arial", 48);
	timerLabel->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	timerLabel->setTag(100);
	this->addChild(timerLabel);

	this->schedule(schedule_selector(TimerTestScene::timerCallback), 1.0);

    return true;
}

void TimerTestScene::timerCallback(float delta)
{
	timer++;
	CCString* str = CCString::createWithFormat("%02d:%02d:%02d", timer / 3600, (timer % 3600) / 60, timer % 60);
	CCLabelTTF* timerLabel = (CCLabelTTF*)this->getChildByTag(100);
	timerLabel->setString(str->getCString());
}