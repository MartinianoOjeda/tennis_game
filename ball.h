#include "player.h"

//BALL
#define BALL 254
#define LEFT -1
#define RIGHT 1
#define UP -1
#define MIDDLE 0
#define DOWN 1

#define COLOR_BALL 33
#define MOVE_BALL_LEFT 1
#define MOVE_BALL_RIGHT 2
#define MOVE_BALL_UP 1
#define MOVE_BALL_MIDDLE 2
#define MOVE_BALL_DOWN 3

#define STARTING_BALL_POSITION_X 36
#define STARTING_BALL_POSITION_Y 15

#define GOAL_PLAYER1 66
#define GOAL_PLAYER2 6

#define SERVE_PLAYER1 8
#define SERVE_PLAYER2 65

#define UPPER_LINE_COLLISION 6
#define LOWER_LINE_COLLISION 24

//DIRECTION VECTOR
//direction[0] = x direction[1] = y
typedef int direction[2];

direction current_dir, previous_dir;

typedef struct ball {
    int X, Y, previous_X, previous_Y, appearance, color;
    direction last_impact;
} Ball;

Ball createBall(int, int, int, int, int, int);
void printBall(Ball);

bool ballInUpperOrLowerLine(Ball);
Ball collisionUpperOrLowerLine(Ball);

bool itIsGoal(Ball);
Ball goal(Ball);

int playerOneOrTwo(Ball, player);
int whatPartOfPlayer(Ball, player);
Ball playerHit(Ball, player);

Ball ballMovement(Ball);
Ball ballAnimation(Ball, player, player);


Ball createBall(int x, int y, int px, int py, int liX, int liY) {
    Ball game_ball;

    game_ball.X = x;
    game_ball.Y = y;
    game_ball.previous_X = px;
    game_ball.previous_Y = py;
    game_ball.last_impact[0] = liX;
    game_ball.last_impact[1] = liY; 
    game_ball.appearance = BALL;
    game_ball.color = COLOR_BALL;

    return game_ball;
}

int playerOneOrTwo(Ball new_ball, player player_hitting) {
    if((new_ball.X == player_hitting.middle.X + 1) && (new_ball.X == PLAYER1_START_POSITION_X + 1)) {

        return 1;
    }
    else {
        if((new_ball.X == player_hitting.middle.X - 1) && (new_ball.X == PLAYER2_START_POSITION_X - 1)) {
            return 2;
        }
        else {
            return 0;
        }
    }
}

int whatPartOfPlayer(Ball new_ball, player player_hitting) {
    if(new_ball.Y == player_hitting.top.Y) {
        return 1;
    }
    else {
        if(new_ball.Y == player_hitting.middle.Y) {
            return 2;
        }
        else {
            if(new_ball.Y == player_hitting.bottom.Y) {
                return 3;
            }
            else {
                return 0;
            }
        }
    }
}

Ball playerHit(Ball new_ball, player player_hitting) {
    
    if((playerOneOrTwo(new_ball, player_hitting) != 0) && (whatPartOfPlayer(new_ball, player_hitting) != 0)) {
        int ph = playerOneOrTwo(new_ball, player_hitting);
        int part = whatPartOfPlayer(new_ball, player_hitting);

        switch(ph) {
            case 1: new_ball.last_impact[0] = MOVE_BALL_RIGHT;
            break;
            case 2: new_ball.last_impact[0] = MOVE_BALL_LEFT;
            break;
        }

        switch(part) {
            case 1: new_ball.last_impact[1] = MOVE_BALL_UP;
            break;
            case 2: new_ball.last_impact[1] = MOVE_BALL_MIDDLE;
            break;
            case 3: new_ball.last_impact[1] = MOVE_BALL_DOWN;
            break;
        }

        return new_ball;
    }
    else {
        return new_ball;
    }
}

bool itIsGoal(Ball new_ball) {
    if((new_ball.X == GOAL_PLAYER1) || (new_ball.X == GOAL_PLAYER2)) {
        return true;
    }
    else {
        return false;
    }
}

Ball goal(Ball new_ball) {
    switch (new_ball.X) {
        case GOAL_PLAYER1: new_ball.X = SERVE_PLAYER1, new_ball.Y = STARTING_BALL_POSITION_Y, new_ball.last_impact[0] = MOVE_BALL_RIGHT, new_ball.last_impact[1] = MOVE_BALL_MIDDLE;/*createBall(SERVE_PLAYER1, STARTING_BALL_POSITION_Y,
                                    new_ball.previous_X, new_ball.previous_Y, MOVE_BALL_RIGHT, MOVE_BALL_MIDDLE);*/
        break;
        case GOAL_PLAYER2: new_ball.X = SERVE_PLAYER2, new_ball.Y = STARTING_BALL_POSITION_Y, new_ball.last_impact[0] = MOVE_BALL_LEFT, new_ball.last_impact[1] = MOVE_BALL_MIDDLE; /*createBall(SERVE_PLAYER2, STARTING_BALL_POSITION_Y,
                                    new_ball.previous_X, new_ball.previous_Y, MOVE_BALL_LEFT, MOVE_BALL_MIDDLE);*/
        break;
    }

    return new_ball;
}

bool ballInUpperOrLowerLine(Ball new_ball) {

    if(new_ball.Y == UPPER_LINE_COLLISION || new_ball.Y == LOWER_LINE_COLLISION) {
        return true;
    }
    else {
        return false;
    }
}

Ball collisionUpperOrLowerLine(Ball new_ball) {

    switch (new_ball.Y) {
        case UPPER_LINE_COLLISION: new_ball.last_impact[1] = MOVE_BALL_DOWN;
        break;
        case LOWER_LINE_COLLISION: new_ball.last_impact[1] = MOVE_BALL_UP;
        break;
    }

    return new_ball;
}

Ball ballMovement(Ball new_ball) {

    switch (new_ball.last_impact[0]) {
        case MOVE_BALL_LEFT: new_ball.X = new_ball.X + LEFT;
        break;
        case MOVE_BALL_RIGHT: new_ball.X = new_ball.X + RIGHT;
        break;
    }

    switch (new_ball.last_impact[1]) {
        case MOVE_BALL_UP: new_ball.Y = new_ball.Y + UP;
        break;
        case MOVE_BALL_MIDDLE: new_ball.Y = new_ball.Y + MIDDLE;
        break;
        case MOVE_BALL_DOWN: new_ball.Y = new_ball.Y + DOWN;
        break;
    }

    return new_ball;
}

void printBall(Ball new_ball) {
    
    if(new_ball.X != new_ball.previous_X || new_ball.Y != new_ball.previous_Y) {
        printf("%c[1;%dm", ESC, new_ball.color);
        gotoXY(new_ball.previous_X, new_ball.previous_Y);
        printf("%c", EMPTY);
        gotoXY(new_ball.X, new_ball.Y);
        printf("%c", new_ball.appearance);
        printf("%c[0m", ESC);
    }
}

Ball ballAnimation(Ball new_ball, player player1, player player2) {
    new_ball.previous_X = new_ball.X;
    new_ball.previous_Y = new_ball.Y;
    
    new_ball = playerHit(new_ball, player1);
    new_ball = playerHit(new_ball, player2);

    if(itIsGoal(new_ball)) {
        new_ball = goal(new_ball);
        Sleep(1000);
    }

    if(ballInUpperOrLowerLine(new_ball)) {
        new_ball = collisionUpperOrLowerLine(new_ball);
    }

    new_ball = ballMovement(new_ball);
    printBall(new_ball);

    return new_ball;
}