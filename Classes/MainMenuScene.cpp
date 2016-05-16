#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    // getting general positioning parameters
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //creating backround
    auto backroundSprite = Sprite::create("Background.png");
    backroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x ,visibleSize.height / 2 + origin.y));
    this->addChild(backroundSprite);
    //creating title Menu
    auto titleSprite = Sprite::create("Title.png");
    titleSprite->setPosition(Point(visibleSize.width/2 + origin.x , visibleSize.height - titleSprite->getContentSize().height));
    this->addChild(titleSprite);
    //creating MenuItem.
    auto PlayItem = MenuItemImage::create("Play Button.png","Play Button Clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    PlayItem->setPosition(Point(visibleSize.width / 2 + origin.x ,visibleSize.height/ 2 + origin.y));
    //creating general menu.
    auto menu = Menu::create(PlayItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);


    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender){
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
}
