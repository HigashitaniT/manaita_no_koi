#include "Recipe9.h"

USING_NS_CC;

CCScene* Recipe9Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe9Scene *layer = Recipe9Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe9Scene::init()
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

	this->schedule(schedule_selector(Recipe9Scene::gameLogic), 3.0);

	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);

	this->scheduleUpdate();

	return true;
}

void Recipe9Scene::addFood()
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
		callfuncN_selector(Recipe9Scene::spriteMoveFinished));
	//------------------
	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Recipe9Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe9Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	bool isCleanUp = true;
	this->removeChild(sprite, isCleanUp);
}

void Recipe9Scene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	//	うっほい君を取得
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float length = sqrt(powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f));
	float dulation = length / winSize.width * 1.5f;
	CCMoveTo* actionMove = CCMoveTo::create(dulation, location);
	player->runAction(actionMove);
}

void Recipe9Scene::update(float dt)
{
	//	うっほい君を取得
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	CCRect playerRect =
		CCRectMake(
		player->getPositionX() - (player->getContentSize().width / 4),
		player->getPositionY() - (player->getContentSize().height / 4),
		player->getContentSize().width / 2,
		player->getContentSize().height / 2
		);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//	ハンバーガー取得
	CCSprite* food = (CCSprite*)this->getChildByTag(2);
	if (food == NULL) return;
	CCRect foodRect =
		CCRectMake(
		food->getPositionX() - (food->getContentSize().width / 2),
		food->getPositionY() - (food->getContentSize().height / 2),
		food->getContentSize().width,
		food->getContentSize().height
		);
	//	衝突判定
	if (playerRect.intersectsRect(foodRect))
	{
		this->removeChild(food, true);
		///	うっほい君のイメージ変更
		player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey02.png"));
		///	01秒後にeatを１度だけ実行させる
		this->scheduleOnce(schedule_selector(Recipe9Scene::eat), 0.1f);
	}
}

void Recipe9Scene::eat(float dt)
{
	//	うっほい君を取得
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	///	うっほい君のイメージ変更
	player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey01.png"));
}

