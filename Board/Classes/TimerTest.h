#ifndef __TIMERTEST_SCENE_H__
#define __TIMERTEST_SCENE_H__

#include "cocos2d.h"
#include <string>

using namespace std;

class TimerTestScene : public cocos2d::CCLayer
{
private:
	int	timer;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
	CREATE_FUNC(TimerTestScene);

	void timerCallback(float delta);

};

#endif // __TIMERTEST_SCENE_H__
