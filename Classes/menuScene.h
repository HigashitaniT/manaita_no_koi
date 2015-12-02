#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class menuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	void tapCallback(CCObject* pSender, CCControlEvent event);
    
	void MakeButton(char* name, int num, CCPoint pos);
    // implement the "static node()" method manually
    CREATE_FUNC(menuScene);
};

#endif // __HELLOWORLD_SCENE_H__
