#include "Recipe7.h"

USING_NS_CC;

CCScene* Recipe7Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe7Scene *layer = Recipe7Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe7Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* player = CCSprite::create("monkey01.png");
	player->setPosition(ccp(player->getContentSize().width * 3 / 2, winSize.height / 2));
	player->setTag(1);
	this->addChild(player);

	this->schedule(schedule_selector(Recipe7Scene::gameLogic), 3.0);
    
	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);
	
	return true;
}

void Recipe7Scene::addFood()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* food = CCSprite::create("hamburger.png");
	food->setPosition(ccp(winSize.width + food->getContentSize().width / 2,
		rand() % (int)winSize.height));
	food->setTag(2);
	this->addChild(food);
	//------------------
	float duration = 2.0f;
	CCMoveTo* actionMove =
		CCMoveTo::create(duration, ccp(
		food->getContentSize().width * 3 / 2,
		food->getPosition().y));
	//------------------
	CCCallFuncN* actionMoveDone =
		CCCallFuncN::create(this,
		callfuncN_selector(Recipe7Scene::spriteMoveFinished));
	//------------------
	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Recipe7Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe7Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	bool isCleanUp = true;
	this->removeChild(sprite, isCleanUp);
}

void Recipe7Scene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	//	‚¤‚Á‚Ù‚¢ŒN‚ðŽæ“¾
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float length = sqrt(powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f));
	float dulation = length / winSize.width * 1.5f;
	CCMoveTo* actionMove = CCMoveTo::create(dulation, location);
	player->runAction(actionMove);
}
