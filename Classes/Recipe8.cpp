#include "Recipe8.h"

USING_NS_CC;

CCScene* Recipe8Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Recipe8Scene *layer = Recipe8Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe8Scene::init()
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

	this->schedule(schedule_selector(Recipe8Scene::gameLogic), 3.0);

	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);

	this->scheduleUpdate();

	return true;
}
void Recipe8Scene::addFood()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *food = CCSprite::create("hamburger.png");
	int height = rand() % (int)winSize.height;
	food->setPosition(ccp(winSize.width + food->getContentSize().width / 2, height));
	food->setTag(2);
	this->addChild(food);

	float duration = 10.0f;

	CCMoveTo* actionMove = CCMoveTo::create(duration, ccp(
		food->getContentSize().width * 3 / 2,
		food->getPosition().y));

	CCCallFuncN* actionMoveDone =
		CCCallFuncN::create(this,
		callfuncN_selector(Recipe8Scene::spriteMoveFinished));

	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));


}

void Recipe8Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe8Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	bool isCleanUp = true;

	this->removeChild(sprite, isCleanUp);
}
void Recipe8Scene::ccTouchesBegan(cocos2d::CCSet*touches, cocos2d::CCEvent*event)
{
	CCTouch*touch = (CCTouch *)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	//うっほい君を取得（tag=1で識別）
	CCSprite*player = (CCSprite *)this->getChildByTag(1);

	//うっほい君をタッチされた座標まで移動させる。
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float length = sqrtf(powf(location.x - player->getPositionX(),
		2.0f) + powf(location.y - player->getPositionY(), 2.0f));
	float duration = length / winSize.width * 1.5f;
	CCMoveTo* actionMove = CCMoveTo::create(duration, location);
	player->runAction(actionMove);
}
void Recipe8Scene::update(float dt)
{

	CCSprite* player = (CCSprite *)this->getChildByTag(1);

	CCRect playerRect = CCRectMake(
		player->getPosition().x - (player->getContentSize().width / 4),
		player->getPosition().y - (player->getContentSize().height / 4),
		player->getContentSize().width / 2,
		player->getContentSize().height / 2);


	CCSprite* food = (CCSprite *)this->getChildByTag(2);
	if (food == NULL) return; 
	CCRect foodRect = CCRectMake(
		food->getPosition().x - (food->getContentSize().width / 2),
		food->getPosition().y - (food->getContentSize().height / 2),
		food->getContentSize().width,
		food->getContentSize().height);

	if (playerRect.intersectsRect(foodRect))
	{
		this->removeChild(food, true);
	}
}
