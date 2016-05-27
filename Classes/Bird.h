#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird
{
public:
   Bird( cocos2d::Layer *layer);

    //fly methodes
    void Fall();
    void Fly(){ IsFalling = false; }; //inline fct
    void StopFliying(){ IsFalling = true; }

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *flappyBird;

	bool IsFalling;

};

#endif // __BIRD_H__
