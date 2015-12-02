#include "Recipe39.h"

#define	MOTION_STREAK_TAG	100

USING_NS_CC;

CCScene* Recipe39Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe39Scene *layer = Recipe39Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe39Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
    
    return true;
}

bool Recipe39Scene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	this->removeChildByTag(MOTION_STREAK_TAG, true);
	CCMotionStreak* streak = CCMotionStreak::create(0.5f, 1, 10, ccc3(255, 255, 0), "line.png");
	this->addChild(streak, 5, MOTION_STREAK_TAG);

	CCPoint point = this->convertTouchToNodeSpace(pTouch);
	streak->setPosition(point);

	return	true;
}

void Recipe39Scene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint point = this->convertTouchToNodeSpace(pTouch);

	CCMotionStreak* streak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
	streak->setPosition(point);
}

