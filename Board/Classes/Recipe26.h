#ifndef __RECIPE26_SCENE_H__
#define __RECIPE26_SCENE_H__

#include "cocos2d.h"

class Recipe26Scene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
	CREATE_FUNC(Recipe26Scene);
};

#endif // __RECIPE26_SCENE_H__
