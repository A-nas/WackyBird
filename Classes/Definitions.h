#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5
#define PIPE_SPAWN_FREQUENCY 0.05 // 0.5 seconde

#define PIPE_GAP 10 // case of flappy birds set the PIPE_GAP * Bird.height * 10 // in my case it will be the windows gap so i will take the same GAP of flappyBirds PIPE_GAP to make it difficul to play
#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35

#define PIPE_MOVEMENT_SPEED 0.1

#define BIRD_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000001

#define BIRD_FALLING_SPEED 0.0025
#define BIRD_FLYING_SPEED 0.00375
#define BIRD_FLY_DURATION 0.25

#endif // __DEFINITIONS_H__
