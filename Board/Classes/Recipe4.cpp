#include "Recipe4.h"

USING_NS_CC;

CCScene* Recipe4Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe4Scene *layer = Recipe4Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe4Scene::init()
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

	this->schedule(schedule_selector(Recipe4Scene::gameLogic), 3.0);
	return true;
}

void Recipe4Scene::addFood()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* food = CCSprite::create("hamburger.png");
	food->setPosition(ccp(winSize.width + food->getContentSize().width / 2,
		rand() % (int)winSize.height));
	food->setTag(2);
	this->addChild(food);
	//------------------
	float duration = 2.0f;
	CCMoveTo* actionMove = CCMoveTo::create(duration, ccp( food->getContentSize().width * 3 / 2, food->getPosition().y));
	//------------------
	food->runAction(actionMove);
}

void Recipe4Scene::gameLogic(float delta)
{
	this->addFood();
}

