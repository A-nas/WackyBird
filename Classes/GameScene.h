#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	// create an inline fct to modify the Physics World later.
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world){ sceneWorld = world; };
    void SpawnPipe(float dt);
    void OnTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event);
    void GoToGameOverScene();
    void StopFlying(float dt);
    void update(float dt);

	cocos2d::PhysicsWorld *sceneWorld;
    Pipe pipe;
    Bird *bird;
};

#endif // __GAME_SCENE_H__
