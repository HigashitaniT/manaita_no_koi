#include "Recipe5.h"

USING_NS_CC;

CCScene* Recipe5Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe5Scene *layer = Recipe5Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe5Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *player = CCSprite::create("monkey01.png");
	player->setPosition(ccp(player->getContentSize().width * 3 / 2, size.height / 2));
	player->setTag(1);
	this->addChild(player);

	this->schedule(schedule_selector(Recipe5Scene::gameLogic), 0.1);

    return true;
}
void Recipe5Scene::addFood()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *food = CCSprite::create("hamburger.png");
	int height = rand() % (int)winSize.height;
	food->setPosition(ccp(winSize.width + food->getContentSize().width / 2, height));
	food->setTag(2);
	this->addChild(food);

	float duration = 1.0f;

	CCMoveTo* actionMove = CCMoveTo::create(duration, ccp(
		food->getContentSize().width * 3 / 2,
		food->getPosition().y));

	CCCallFuncN* actionMoveDone =
		CCCallFuncN::create(this,
		callfuncN_selector(Recipe5Scene::spriteMoveFinished));

	food->runAction(
		CCSequence::create(actionMove, actionMoveDone,NULL));


}

void Recipe5Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe5Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	bool isCleanUp = true;

	this->removeChild(sprite, isCleanUp);
}