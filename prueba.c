#include "ball.h"

int main() {
    int game_over = 0;
    char key = 0;
    player p1, p2;
    Ball b;

    system("cls");
    
    hideCursor();

    drawCourt();
    
    
    p1 = createPlayer(1, "Player", COLOR_PLAYER1);
    p2 = createPlayer(2, "Player", COLOR_PLAYER1);
    b = createBall(STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y,
               STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y, MOVE_BALL_RIGHT, MOVE_BALL_UP);

    while(!game_over) {

        key = 0;

        if(kbhit()) {
            key = getch();
            game_over = (key == ESC);
        }

        if(p1.middle.Y != p1.middle.previous_Y) {
            p1.top.previous_Y = p1.top.Y;
            p1.middle.previous_Y = p1.middle.Y;
            p1.bottom.previous_Y = p1.bottom.Y;
        }

        if(key != 0) {
            if(key == P1_UP) {
                p1.bottom.Y = p1.bottom.Y + UP;
                p1.middle.Y = p1.middle.Y + UP;
                p1.top.Y = p1.top.Y + UP;
            }
            else {
                if(key == P1_DOWN) {
                    p1.bottom.Y = p1.bottom.Y + DOWN;
                    p1.middle.Y = p1.middle.Y + DOWN;
                    p1.top.Y = p1.top.Y + DOWN;
                }
            }
        }
        b = ballAnimation(b, p1, p2);
        printPlayer(p1);
        printPlayer(p2);
        Sleep(16);
    }

    return 0;
}