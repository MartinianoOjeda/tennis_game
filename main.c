#include "ball.h"

int main() {
    int game_over = 0;
    int t = 0;
    char key = 0;
    Ball new_ball;

    system("cls");
    
    drawCourt();
    
    new_ball = createBall(34, 15, 0, 0, MOVE_BALL_LEFT, MOVE_BALL_DOWN);
    
    while(!game_over) {
        
        new_ball = ballAnimation(new_ball);

        if(kbhit()) {
            key = getch();
            game_over = (key == ESC);
        }
    }
    

    return 0;
}