#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer){
    CCLOG( "SPAWN PIPE !!" );
    auto topPipe = Sprite::create("Pipe.png");
    auto bottomPipe = Sprite::create("Pipe.png");

    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

    auto random = CCRANDOM_0_1();

     if( random < LOWER_SCREEN_PIPE_THRESHOLD ){

        random = LOWER_SCREEN_PIPE_THRESHOLD;
     }
     else if( random > UPPER_SCREEN_PIPE_THRESHOLD ){

        random = UPPER_SCREEN_PIPE_THRESHOLD;
     }

     auto topPipePosition = ( random * visibleSize.height) + (topPipe->getContentSize().height/2 );

     topPipeBody->setDynamic(false);
     bottomPipeBody->setDynamic(false);

     topPipe->setPhysicsBody(topPipeBody);
     bottomPipe->setPhysicsBody(bottomPipeBody);

     topPipe->setPosition(Point(visibleSize.width/2 + topPipe->getContentSize().width + origin.x + CCRANDOM_MINUS1_1() * 250 , topPipePosition));
     bottomPipe->setPosition(Point(topPipe->getPositionX()
                            ,topPipePosition - (Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));

    // topPipe->setPosition(Point(origin.x + CCRANDOM_MINUS1_1(), origin.y));

    // topPipe->setPosition(Point(visibleSize.width/2 + origin.x + visibleSize.width/4,visibleSize.height/2 + origin.y + CCRANDOM_0_1() + visibleSize.height/4));

     layer->addChild(topPipe);
     layer->addChild(bottomPipe);
}

void Pipe::SpawnPipe1( cocos2d::Layer *layer )
{
    CCLOG( "SPAWN PIPE" );
    
    auto topPipe = Sprite::create( "Pipe.png" );
    auto bottomPipe = Sprite::create( "Pipe.png" );
    
    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize( ) );
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize( ) );
   /* 
    auto random = CCRANDOM_0_1( );
    
    if ( random < LOWER_SCREEN_PIPE_THRESHOLD )
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD )
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    
    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize().height / 2 ); */
    
    topPipeBody->setDynamic( false );
    bottomPipeBody->setDynamic( false );
    
    topPipe->setPhysicsBody( topPipeBody );
    bottomPipe->setPhysicsBody( bottomPipeBody );

    //collision handle
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setContactTestBitmask(true);
    
    //topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize().width + origin.x
    //                            ,topPipePosition ) );

    //bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "Ball.png" )->getContentSize( ).height * PIPE_GAP ) - topPipe->getContentSize().height ) );

    // new pipes position
    //setting the random number between min and max
    auto minY = origin.y
                + Sprite::create( "Ball.png" )->getContentSize( ).height/4
                - (topPipe->getContentSize().height/2);
    
    auto maxY = origin.y 
                - Sprite::create( "Ball.png" )->getContentSize( ).height/4
                - Sprite::create( "Ball.png" )->getContentSize( ).height
                - Sprite::create( "Ball.png" )->getContentSize( ).height/3
                + visibleSize.height
                - topPipe->getContentSize().height/2;
    
    //float randNum = rand()% (float)(maxY-minY + 1.0) + minY;
    float randNum = minY + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxY-minY)));
    //setting position
    bottomPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x
                                  ,randNum));

    topPipe->setPosition(Point(bottomPipe->getPositionX()
                               ,bottomPipe->getPositionY() + Sprite::create( "Ball.png" )->getContentSize( ).height + (Sprite::create( "Ball.png" )->getContentSize( ).height/3) + (topPipe->getContentSize().height)));
    // end new pipe possition

    layer->addChild( topPipe );
    layer->addChild( bottomPipe );

    auto topPipeAction = MoveBy::create (PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5 , 0));
    auto bottomPipeAction = MoveBy::create (PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5 , 0));

    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);
}