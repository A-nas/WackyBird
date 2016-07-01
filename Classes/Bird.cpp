#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer ){
    IsFalling = true;
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    flappyBird = Sprite::create("Ball.png");
    flappyBird->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));

    auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);
    flappyBird->setPhysicsBody(flappyBody);

    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);

    layer->addChild(flappyBird, 100 );

}

void Bird::Fall(){
    if(true == IsFalling){
        flappyBird->setPositionX(visibleSize.width/2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
    }else{
        flappyBird->setPositionX(visibleSize.width/2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() + (BIRD_FALLING_SPEED * visibleSize.height));
    }
}
void Bird::Fly(){IsFalling = true;}
void Bird::StopFliying();