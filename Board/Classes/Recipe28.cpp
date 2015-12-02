#include "Recipe28.h"

#define	FLIP_DURATION	1.0f
#define CARD_FACE_TAG	1
#define	CARD_BACK_TAG	2

USING_NS_CC;

CCScene* Recipe28Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe28Scene *layer = Recipe28Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe28Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	rotateSpeed = FLIP_DURATION;
	flipCard();
    
    return true;
}

void Recipe28Scene::flipCard()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//	裏面カード
	CCSprite* card = CCSprite::create("card.png");
	card->setPosition(size / 2);
	this->addChild(card, CARD_FACE_TAG, CARD_FACE_TAG);
	card->setVisible(false);

	//	表面カード
	CCSprite* card2 = CCSprite::create("card_face.png");
	card2->setPosition(card->getPosition());
	this->addChild(card2, CARD_BACK_TAG, CARD_BACK_TAG);

	//	カードめくるアクション
	CCOrbitCamera* turn = CCOrbitCamera::create(rotateSpeed / 2.0f, 1, 0, 0, 90, 0, 0);
	CCHide* hide = CCHide::create();
	CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Recipe28Scene::flipCard2));
	card2->runAction(CCSequence::create(turn, hide, func, NULL));
}

void Recipe28Scene::flipCard2()
{
	CCSprite* card = (CCSprite*)this->getChildByTag(CARD_FACE_TAG);
	CCShow* show = CCShow::create();
	CCShow* hide = CCShow::create();
	CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Recipe28Scene::flipCard3));
	CCOrbitCamera* turn = CCOrbitCamera::create(rotateSpeed / 2.0f, 1, 0, 270, 180, 0, 0);
	card->runAction(CCSequence::create(show, turn, hide, func, NULL));
	if (rotateSpeed > 0.1f)
		rotateSpeed -= 0.05f;
}

void Recipe28Scene::flipCard3()
{
	CCSprite* card = (CCSprite*)this->getChildByTag(CARD_BACK_TAG);
	CCShow* show = CCShow::create();
	CCShow* hide = CCShow::create();
	CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Recipe28Scene::flipCard2));
	CCOrbitCamera* turn = CCOrbitCamera::create(rotateSpeed / 2.0f, 1, 0, 90, 180, 0, 0);
	card->runAction(CCSequence::create(show, turn, hide, func, NULL));
	if (rotateSpeed > 0.1f)
		rotateSpeed -= 0.05f;
}