#include "Recipe12.h"

USING_NS_CC;

CCScene* Recipe12Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe12Scene *layer = Recipe12Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe12Scene::init()
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

	this->schedule(schedule_selector(Recipe12Scene::gameLogic), 3.0);

	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);

	this->scheduleUpdate();
	this->m_points = 0;
	CCLabelTTF* scoreLabel =
		CCLabelTTF::create("SCORE", "arial", 48);
	scoreLabel->setPosition(ccp(
		winSize.width / 2,
		winSize.height - scoreLabel->getContentSize().height / 2));
	scoreLabel->setTag(10);
	this->addChild(scoreLabel);

	CCLabelTTF* pointLabel =
		CCLabelTTF::create("0", "arial", 48);
	pointLabel->setPosition(ccp(
		scoreLabel->getPositionX() + scoreLabel->getContentSize().width,
		winSize.height - pointLabel->getContentSize().height / 2));
	pointLabel->setTag(11);
	this->addChild(pointLabel);

	return true;
}

void Recipe12Scene::addFood()
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
		callfuncN_selector(Recipe12Scene::spriteMoveFinished));
	//------------------
	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Recipe12Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe12Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	bool isCleanUp = true;
	this->removeChild(sprite, isCleanUp);
}

void Recipe12Scene::ccTouchesBegan(CCSet* touches, CCEvent* event)
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

void Recipe12Scene::update(float dt)
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
		this->scheduleOnce(schedule_selector(Recipe12Scene::eat), 0.1f);
	}
}

void Recipe12Scene::eat(float dt)
{
	//	うっほい君を取得
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	///	うっほい君のイメージ変更
	player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey01.png"));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->m_points +=
		player->getPositionX() / (winSize.width / 4) + 1;
	CCLabelTTF* label =
		(CCLabelTTF*)this->getChildByTag(11);
	CCString* points = CCString::createWithFormat(
		"%d", this->m_points);
	label->setString(points->getCString());
}

