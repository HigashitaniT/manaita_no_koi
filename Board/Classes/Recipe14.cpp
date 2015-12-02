#include "Recipe14.h"

USING_NS_CC;

CCScene* Recipe14Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Recipe14Scene *layer = Recipe14Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Recipe14Scene::init()
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

	this->schedule(schedule_selector(Recipe14Scene::gameLogic), 3.0);

	this->setTouchMode(kCCTouchesAllAtOnce);
	this->setTouchEnabled(true);

	this->scheduleUpdate();
	this->m_points = 0;
	this->m_actionType = 0;
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

void Recipe14Scene::addFood()
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
		callfuncN_selector(Recipe14Scene::spriteMoveFinished));
	//------------------
	food->runAction(
		CCSequence::create(actionMove, actionMoveDone, NULL));
	CCActionInterval* action1;
	CCActionInterval* action2;
	///	�x�W�F�Ȑ��ړ��̍ۂɗ��p
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(winSize.width, winSize.height);
	bezier.controlPoint_2 = ccp(winSize.width / 2, -winSize.height);
	bezier.endPosition = ccp(0, winSize.height);
	///	�A�N�V�����̎�ނ�؂�ւ��Ď��s
	switch (this->m_actionType)
	{
	case	1:
		///	�g��F�S�{�Ɋg��
		action1 = CCScaleTo::create(duration, 4.0f);
		food->runAction(action1);
		break;
	case	2:
		///	��]�R�U�O�x
		action1 = CCRotateBy::create(duration, 360);
		food->runAction(action1);
		break;
	case	3:
		///	�g��Ɖ�]�̑g�ݍ��킹
		action1 = CCScaleTo::create(duration, 4.0f);
		action2 = CCRotateBy::create(duration, 360);
		food->runAction(action1);
		food->runAction(action2);
		break;
	case	4:
		///	�i���J��Ԃ�
		action1 = CCRotateBy::create(0.5f, -360);
		///	0.5�b�łP��]���i���ɌJ��Ԃ��i�폜�����܂Łj
		action2 = CCRepeatForever::create(action1);
		food->runAction(action2);
		break;
	case	5:
		///	�W�����v�F�����P�O�O�A�񐔂T
		action1 = CCJumpBy::create(duration, ccp(0, 0), 100, 5);
		food->runAction(action1);
		break;
	case 6:
		// �V�[�P���X���s�F�S�{�Ɋg�債����A�R��W�����v
		action1 = CCScaleTo::create(duration / 2.0f, 4.0f);
		action2 = CCJumpBy::create(duration / 2.0f, ccp(0, 0), 100, 3);
		food->runAction(CCSequence::create(action1, action2, NULL));
		break;
	case 7:
		// �t�F�[�h�C���^�A�E�g
		// �����̎��ԂŃt�F�[�h�C��
		action1 = CCFadeIn::create(duration / 2.0f);
		// �t�F�[�h�C���̔��]
		action2 = action1->reverse();
		// �t�F�[�h�C���̔��]�͈ȉ��Ɠ���
		//action2 = CCFadeOut::create(duration/2.0f);
		// action1�Aaction2 �̏��Ɏ��s
		food->runAction(CCSequence::create(action1, action2, NULL));
		break;
	case 8:
		// �����ړ��̃A�N�V�������~
		food->stopAllActions();
		// �x�W�F�Ȑ��ɉ����Ĉړ�
		action1 = CCBezierTo::create(duration, bezier);
		food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
		break;
	case 9:
		// �����ړ��̃A�N�V�������~
		food->stopAllActions();
		// EaseInOut�A�N�V�������쐬
		action1 = CCEaseInOut::create((CCActionInterval *)actionMove, 3.0f);
		food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
		break;
	case 10:
		// �����ړ��̃A�N�V�������~
		food->stopAllActions();
		// CCEaseBounceOut�A�N�V�������쐬
		action1 = CCEaseBounceOut::create((CCActionInterval *)actionMove);
		food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
		break;
	case 11:
		// �����ړ��̃A�N�V�������~
		food->stopAllActions();
		// CCEaseBounceOut�A�N�V�������쐬
		action1 = CCEaseBounceOut::create((CCActionInterval *)actionMove);
		food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
		// �W�����v�F����100�A��5
		action2 = CCJumpBy::create(duration, ccp(0, 0), 100, 5);
		// �W�����v�������Ɏ��s
		food->runAction(action2);
		break;
	default:
		break;
	}
	this->m_actionType = (this->m_actionType + 1) % 12;
}

void Recipe14Scene::gameLogic(float delta)
{
	this->addFood();
}

void Recipe14Scene::spriteMoveFinished(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	bool isCleanUp = true;
	this->removeChild(sprite, isCleanUp);
}

void Recipe14Scene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	//	�����ق��N���擾
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float length = sqrt(powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f));
	float dulation = length / winSize.width * 1.5f;
	CCMoveTo* actionMove = CCMoveTo::create(dulation, location);
	player->runAction(actionMove);
}

void Recipe14Scene::update(float dt)
{
	//	�����ق��N���擾
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	CCRect playerRect =
		CCRectMake(
		player->getPositionX() - (player->getContentSize().width / 4),
		player->getPositionY() - (player->getContentSize().height / 4),
		player->getContentSize().width / 2,
		player->getContentSize().height / 2
		);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//	�n���o�[�K�[�擾
	CCSprite* food = (CCSprite*)this->getChildByTag(2);
	if (food == NULL) return;
	CCRect foodRect =
		CCRectMake(
		food->getPositionX() - (food->getContentSize().width / 2),
		food->getPositionY() - (food->getContentSize().height / 2),
		food->getContentSize().width,
		food->getContentSize().height
		);
	//	�Փ˔���
	if (playerRect.intersectsRect(foodRect))
	{
		this->removeChild(food, true);
		///	�����ق��N�̃C���[�W�ύX
		player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey02.png"));
		///	01�b���eat���P�x�������s������
		this->scheduleOnce(schedule_selector(Recipe14Scene::eat), 0.1f);
	}
}

void Recipe14Scene::eat(float dt)
{
	//	�����ق��N���擾
	CCSprite* player = (CCSprite*)this->getChildByTag(1);
	///	�����ق��N�̃C���[�W�ύX
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

