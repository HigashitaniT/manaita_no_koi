#ifndef __RECIPE39_SCENE_H__
#define __RECIPE39_SCENE_H__

#include "cocos2d.h"

class Recipe39Scene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

    // implement the "static node()" method manually
	CREATE_FUNC(Recipe39Scene);
};

#endif // __RECIPE39_SCENE_H__
