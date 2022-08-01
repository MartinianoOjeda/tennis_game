#include "tennis.h"

//BALL
#define BALL 254
#define COLOR_BALL 33
#define MOVE_BALL_LEFT 1
#define MOVE_BALL_RIGHT 2
#define MOVE_BALL_UP 1
#define MOVE_BALL_MIDDLE 2
#define MOVE_BALL_DOWN 3

//DIRECTION VECTOR
//direction[0] = x direction[1] = y
typedef int direction[2];

direction current_dir, previous_dir;

typedef struct ball {
    int X, Y, previous_X, previous_Y, AP, COLOR;
    direction last_impact;
} Ball;

Ball createBall(int, int, int, int, int, int);
void printBall(Ball);
bool ballInLeftOrRightEdge(Ball);
bool ballInUpperOrLowerEdge(Ball);
int ballCollision(Ball);

Ball ballAnimation(Ball);


Ball createBall(int x, int y, int px, int py, int liX, int liY) {
    Ball game_ball;

    game_ball.X = x;
    game_ball.Y = y;
    game_ball.previous_X = px;
    game_ball.previous_Y = py;
    game_ball.last_impact[0] = liX;
    game_ball.last_impact[1] = liY; 
    game_ball.AP = BALL;
    game_ball.COLOR = COLOR_BALL;

    return game_ball;
}

void printBall(Ball new_ball) {
    printf("%c[1;%dm", ESC, new_ball.COLOR);
    gotoXY(new_ball.previous_X, new_ball.previous_Y);
    printf("%c", EMPTY);
    gotoXY(new_ball.X, new_ball.Y);
    printf("%c", new_ball.AP);
    printf("%c[0m", ESC);
    gotoXY(0,0);
}

bool ballInLeftOrRightEdge(Ball new_ball) {

    if(new_ball.X == STARTING_POINT_X + 1 || new_ball.X == COURT_WIDTH_X + 5) {
        return true; 
    }
    else {
        return false;
    }
}

bool ballInUpperOrLowerEdge(Ball new_ball) {

    if(new_ball.Y == STARTING_POINT_Y + 1 || new_ball.Y == COURT_HIGHT_Y + 5) {
        return true;
    }
    else {
        return false;
    }
}

Ball ballAnimation(Ball new_ball) {
    new_ball.previous_X = new_ball.X;
    new_ball.previous_Y = new_ball.Y;

    if(ballInLeftOrRightEdge(new_ball)) {
        switch (new_ball.X) {
            case STARTING_POINT_X + 1: new_ball.last_impact[0] = MOVE_BALL_RIGHT;
            break;
            case COURT_WIDTH_X + 5: new_ball.last_impact[0] = MOVE_BALL_LEFT;
            break;
        }
    }

    if(ballInLeftOrRightEdge(new_ball) && (new_ball.Y <= 6 || new_ball.Y >= 15)) {
        int y = 0;
        y = (new_ball.Y <= 6);

        if(new_ball.Y >= 15) {
            y = 2;
        }
        
        switch (y) {
            case 1: new_ball.last_impact[1] = MOVE_BALL_UP;
            break;
            case 2: new_ball.last_impact[1] = MOVE_BALL_DOWN;
            break;
        }
    }

    if(ballInUpperOrLowerEdge(new_ball)) {

        switch (new_ball.Y) {
            case STARTING_POINT_Y + 1: new_ball.last_impact[1] = MOVE_BALL_DOWN;
            break;
            case COURT_HIGHT_Y + 5: new_ball.last_impact[1] = MOVE_BALL_UP;
            break;
        }
    }

    switch (new_ball.last_impact[0]) {
        case MOVE_BALL_LEFT: new_ball.X = new_ball.X - 1;
        break;
        case MOVE_BALL_RIGHT: new_ball.X = new_ball.X + 1;
        break;
    }

    switch (new_ball.last_impact[1]) {
        case MOVE_BALL_UP: new_ball.Y = new_ball.Y - 1;
        break;
        case MOVE_BALL_MIDDLE: new_ball.Y = new_ball.Y + 0;
        break;
        case MOVE_BALL_DOWN: new_ball.Y = new_ball.Y + 1;
        break;
    }

    printBall(new_ball);
    Sleep(50);

    return new_ball;
}


