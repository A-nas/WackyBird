#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL ); //PROBLEM TO DRAW DEBUG MODE :(
    //addChild(B2DebugDrawLayer::create( scene , 32 ) , 9999 ); integration de github didnt work :(
    // try this on the top with the two libraries included on the android mk file
//#if CC_ENABLE_CHIPMUNK_INTEGRATION
//    _debugLayer->setVisible(! _debugLayer->isVisible());
//#endif
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );
    // add layer as a child to scene
    PhysicsWorld* world = scene->getPhysicsWorld();
    auto gravity = Vec2(0.0f, 0.0f);
    world->setGravity(gravity);
    /*
    PhysicsWorld* world = scene->getPhysicsWorld();
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create([=](Acceleration*
    acc, Event* event){
    auto gravity = Vec2(acc->x*400.0f, acc->y*400.0f);
    world->setGravity(gravity);
    });
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scene);
    */


    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //adding a backround
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x ,visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    //collision detection
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x ,visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    //spawning pipes selon la largeur du device utilisé
    this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width); // * visibleSize.width (multiPlatform)
    bird = new Bird(this); // bird recois ladresse de linstance de lobjet crée + create the bird on the layer (GameScene here) with the pointer.
    //collision test
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact& contact){
    CCLOG("contact begin");
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();
    //add here the gameOverScene redirection !
    //Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    auto scene = GameOverScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME , scene ));
    return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    //End collision test

    //Add tap listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    //CC_CALLBACK_2(GameScene::OnTouchBegan , this); is not working :( 
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event){
        CCLOG("TOUCHED !!!");
        bird->Fly(); //* jni/../../../Classes/GameScene.cpp:89:9: error: 'this' was not captured for this lambda function
        this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION); //* jni/../../../Classes/GameScene.cpp:89:9: error: 'this' was not captured for this lambda function
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener , this);
    // End tap listener
    this->scheduleUpdate();

    return true;
}

void GameScene::SpawnPipe(float dt){
    pipe.SpawnPipe1(this);
}

void GameScene::OnTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event){

}


// je ne peux pas appeler cette fonction a l'interieur du listener error : this was not captured for this lambda fucntion
void GameScene::GoToGameOverScene(){
    auto scene = GameOverScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME , scene ));
}



// methode for fly

void GameScene::StopFlying(float dt){
    bird->StopFliying();
}

void GameScene::update(float dt){
    bird->Fall();
}