//#include "ball.h"
#include "tennis.h"

#define PLAYER 219
#define COLOR_PLAYER 31

#define PLAYER1_START_POSITION_X 6
#define PLAYER2_START_POSITION_X 66
#define PLAYERS_START_POSITION_Y 15

typedef char name[7];

typedef struct part {
    int X, Y, previous_Y, part, color;
} player_part;

typedef struct players {
    player_part top, middle, bottom;
    name player_name;
    int number;
}player;


player createPlayer(int, name);
void printPlayer(player);
void playerMovement(player);


player createPlayer(int number, name player_name) {
    player new_player;

    new_player.number = number;
    strcpy(new_player.player_name, player_name);
    
    switch(number) {
        case 1: new_player.top.X = PLAYER1_START_POSITION_X,
                new_player.middle.X = PLAYER1_START_POSITION_X,
                new_player.bottom.X = PLAYER1_START_POSITION_X;
        break;
        case 2: new_player.top.X = PLAYER2_START_POSITION_X,
                new_player.middle.X = PLAYER2_START_POSITION_X,
                new_player.bottom.X = PLAYER2_START_POSITION_X;
        break;
    }

    new_player.top.Y = PLAYERS_START_POSITION_Y - 1;
    new_player.middle.Y = PLAYERS_START_POSITION_Y;
    new_player.bottom.Y = PLAYERS_START_POSITION_Y + 1;

    new_player.top.part = PLAYER;
    new_player.middle.part = PLAYER;
    new_player.bottom.part = PLAYER;

    new_player.top.color = COLOR_PLAYER;
    new_player.middle.color = COLOR_PLAYER;
    new_player.bottom.color = COLOR_PLAYER;

    return new_player;
}

void printPlayer(player new_player) {
    printf("%c[1;%dm", ESC, new_player.middle.color);
    gotoXY(new_player.top.X, new_player.top.Y);
    printf("%c", EMPTY);
    gotoXY(new_player.middle.X, new_player.middle.Y);
    printf("%c", EMPTY);
    gotoXY(new_player.bottom.X, new_player.bottom.Y);
    printf("%c", EMPTY);

    gotoXY(new_player.top.X, new_player.top.Y);
    printf("%c", new_player.top.part);
    gotoXY(new_player.middle.X, new_player.middle.Y);
    printf("%c", new_player.middle.part);
    gotoXY(new_player.bottom.X, new_player.bottom.Y);
    printf("%c", new_player.bottom.part);

    printf("%c[0m", ESC);
}

void playerMovement(player new_player) {

}

