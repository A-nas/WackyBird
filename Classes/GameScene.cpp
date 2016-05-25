#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"



USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    //scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL ); //PROBLEM TO DRAW DEBUG MODE :(
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );
    // add layer as a child to scene
    
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
    

    return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    //End collision test

    //Add tap listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    //CC_CALLBACK_2(GameScene::OnTouchBegan , this); is not working :( 
    touchListener->onTouchBegan = [](cocos2d::Touch *touch,cocos2d::Event *event){
        CCLOG("TOUCHED !!!");
    }
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener , this);
    // End tap listener




    return true;
}

void GameScene::SpawnPipe(float dt){
    pipe.SpawnPipe1(this);
}

void GameScene::OnTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event){

}

void GameScene::GoToGameOverScene(float dt){
    auto scene = GameOverScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME , scene ));
}

