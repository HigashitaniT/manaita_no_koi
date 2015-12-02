#ifndef __RECIPE4_SCENE_H__
#define __RECIPE4_SCENE_H__

#include "cocos2d.h"

class Recipe4Scene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void addFood();

	void gameLogic(float delta);

    // implement the "static node()" method manually
    CREATE_FUNC(Recipe4Scene);
};

#endif // __RECIPE4_SCENE_H__
