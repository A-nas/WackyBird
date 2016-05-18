#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    // create the scene as Physics World
    auto scene = Scene::createWithPhysics();
    //* set all physics object strokes in red (must be disabled when publish game)
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    // **set the layer of te same physics world of scene
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
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
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x ,visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    //spawning pipes selon la largeur du device utilisé
    this->schedule(schedule_selector(GameScene::SpawnPipe),PIPE_SPAWN_FREQUENCY * visibleSize.width ); // * visibleSize.width (multiPlatform)

    return true;
}

void GameScene::SpawnPipe(float dt){
    pipe.SpawnPipe(this);
}