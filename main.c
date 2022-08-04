#include "ball.h"

int main() {
    int game_over = 0;
    int time = 0;
    char key = 0;
    Ball b;
    player p1, p2;

    system("cls");
    
    hideCursor();

    drawCourt();
    
    p1 = createPlayer(1, "Player", COLOR_PLAYER1);
    p2 = createPlayer(2, "Player", COLOR_PLAYER2);
    b = createBall(STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y, 0, 0, MOVE_BALL_RIGHT, MOVE_BALL_UP);

    while(!game_over) {

        key = 0;

        if(kbhit()) {
            key = getch();
            game_over = (key == ESC);
        }
        
        if(key == P1_UP || key == P1_DOWN) {
            p1 = playersAnimation(key, p1);
        }
        if(key == P2_UP || key == P2_DOWN) {
            p2 = playersAnimation(key, p2);
        }
        
        b = ballAnimation(b, p1, p2);
        printPlayer(p1);
        printPlayer(p2);
        Sleep(FRAMERATE);
    }
    
    return 0;
}