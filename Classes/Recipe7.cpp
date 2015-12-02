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
    
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *player = CCSprite::create("monkey01.png");
	player->setPosition(ccp(player->getContentSize().width * 3 / 2, size.height / 2));
	player->setTag(1);
	this->addChild(player);

	this->schedule(schedule_selector(Recipe7Scene::gameLogic), 0.1);

	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);

	return true;
}
void Recipe7Scene::addFood()
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
		callfuncN_selector(Recipe7Scene::spriteMoveFinished));

	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));


}

void Recipe7Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe7Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	bool isCleanUp = true;

	this->removeChild(sprite, isCleanUp);
}
void Recipe7Scene::ccTouchesBegan(cocos2d::CCSet*touches, cocos2d::CCEvent*event)
{
	CCTouch*touch = (CCTouch *)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	//うっほい君を取得（tag=1で識別）
	CCSprite*player = (CCSprite *)this->getChildByTag(1);

	//うっほい君をタッチされた座標まで移動させる
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//継続時間は移動距離に比例させる
	float length = sqrtf(powf(location.x - player->getPositionX(),
		2.0f) + powf(location.y - player->getPositionY(), 2.0f));
	float duration = length / winSize.width * 1.5f;
	CCMoveTo* actionMove = CCMoveTo::create(duration, location);
	player->runAction(actionMove);
}