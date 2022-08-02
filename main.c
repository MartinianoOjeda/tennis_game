#include "ball.h"

int main() {
    int game_over = 0;
    int t = 0;
    char key = 0;
    Ball new_ball;
    player player1, player2;

    system("cls");
    
    drawCourt();
    
    player1 = createPlayer(1, "Player");
    player2 = createPlayer(2, "Player");

    new_ball = createBall(STARTING_BALL_POSITION_X, STARTING_BALL_POSITION_Y, 0, 0, MOVE_BALL_LEFT, MOVE_BALL_MIDDLE);
    
    while(!game_over) {
        
        printPlayer(player1);
        printPlayer(player2);
        ballAnimation(new_ball, player1, player2);

        if(kbhit()) {
            key = getch();
            game_over = (key == ESC);
        }
    }
    

    return 0;
}