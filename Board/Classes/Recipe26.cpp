#include "Recipe26.h"

USING_NS_CC;

CCScene* Recipe26Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe26Scene *layer = Recipe26Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe26Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	pSprite->setPosition(visibleSize / 2);
	pSprite->setScale(2);
	pSprite->setTag(2);

	CCSprite* pMask = CCSprite::create("mask_star.png");
	pMask->setPosition(visibleSize / 2);

	CCClippingNode* pClip = CCClippingNode::create();
	pClip->setStencil(pMask);
	pClip->setAlphaThreshold(0);
	pClip->addChild(pSprite);
	pClip->setTag(1);

	this->addChild(pClip);

    return true;
}

