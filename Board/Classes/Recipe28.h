#ifndef __RECIPE28_SCENE_H__
#define __RECIPE28_SCENE_H__

#include "cocos2d.h"

class Recipe28Scene : public cocos2d::CCLayer
{
private:
	float rotateSpeed;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void flipCard();

	void flipCard2();

	void flipCard3();
	// implement the "static node()" method manually
	CREATE_FUNC(Recipe28Scene);
};

#endif // __RECIPE28_SCENE_H__
