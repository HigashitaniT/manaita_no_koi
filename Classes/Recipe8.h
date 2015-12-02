#ifndef __RECIPE8_SCENE_H__
#define __RECIPE8_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Recipe8Scene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void addFood();

	void gameLogic(float delta);

	void spriteMoveFinished(CCNode* sender);

	void Recipe8Scene::ccTouchesBegan(cocos2d::CCSet*touches, cocos2d::CCEvent*event);

	void Recipe8Scene::update(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(Recipe8Scene);
};

#endif // __RECIPE8_SCENE_H__
