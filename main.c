#include "ball.h"

int main() {
    int game_over = 0;
    int time = 0;
    char key = 0;
    Ball new_ball;
    player player1, player2;

    system("cls");
    
    hideCursor();

    drawCourt();
    
    player1 = createPlayer(1, "Player", COLOR_PLAYER1);
    player2 = createPlayer(2, "Player", COLOR_PLAYER2);
    new_ball = createBall(STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y,
               STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y, MOVE_BALL_RIGHT, MOVE_BALL_UP);

    while(!game_over) {

        key = 0;

        if(kbhit()) {
            key = getch();
            game_over = (key == ESC);
        }
        
        player1 = animationPlayers(key, player1);
        player2 = animationPlayers(key, player2);
        new_ball = ballAnimation(new_ball, player1, player2);
        Sleep(FRAMERATE);
    }
    
    return 0;
}