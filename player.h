#include "tennis.h"

#define PLAYER 219

#define PLAYER1_START_POSITION_X 6
#define PLAYER2_START_POSITION_X 66
#define PLAYERS_START_POSITION_Y 15

//KEYS
#define P1_UP 97 //A
#define P1_DOWN 100 //D
#define P2_UP 75 //K
#define P2_DOWN 77 //M

typedef char name[7];

typedef struct part {
    int X, Y, previous_Y, part, color;
} player_part;

typedef struct players {
    player_part top, middle, bottom;
    name player_name;
    int number;
}player;


player createPlayer(int, name, int);
void printPlayer(player);
player playersAnimation(int, player);


player createPlayer(int number, name player_name, int color) {
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
    new_player.top.previous_Y = PLAYERS_START_POSITION_Y - 1;
    new_player.middle.Y = PLAYERS_START_POSITION_Y;
    new_player.middle.previous_Y = PLAYERS_START_POSITION_Y;
    new_player.bottom.Y = PLAYERS_START_POSITION_Y + 1;
    new_player.bottom.previous_Y = PLAYERS_START_POSITION_Y + 1;

    new_player.top.part = PLAYER;
    new_player.middle.part = PLAYER;
    new_player.bottom.part = PLAYER;

    new_player.top.color = color;
    new_player.middle.color = color;
    new_player.bottom.color = color;

    return new_player;
}

void printPlayer(player new_player) {
    printf("%c[1;%dm", ESC, new_player.middle.color);
    gotoXY(new_player.top.X, new_player.top.previous_Y);
    printf("%c", EMPTY);
    gotoXY(new_player.middle.X, new_player.middle.previous_Y);
    printf("%c", EMPTY);
    gotoXY(new_player.bottom.X, new_player.bottom.previous_Y);
    printf("%c", EMPTY);
    gotoXY(new_player.top.X, new_player.top.Y);
    printf("%c", new_player.top.part);
    gotoXY(new_player.middle.X, new_player.middle.Y);
    printf("%c", new_player.middle.part);
    gotoXY(new_player.bottom.X, new_player.bottom.Y);
    printf("%c", new_player.bottom.part);
    printf("%c[0m", ESC);
}

player playersAnimation(int key, player p) {
    if(p.middle.Y != p.middle.previous_Y) {
            p.top.previous_Y = p.top.Y;
            p.middle.previous_Y = p.middle.Y;
            p.bottom.previous_Y = p.bottom.Y;
    }

    if(key != 0) {
        if(key == P1_UP || key == P2_UP) {
            p.bottom.Y = p.bottom.Y - 1;
            p.middle.Y = p.middle.Y - 1;
            p.top.Y = p.top.Y - 1;
        }
        
        if(key == P1_DOWN || key == P2_DOWN) {
            p.bottom.Y = p.bottom.Y + 1;
            p.middle.Y = p.middle.Y + 1;
            p.top.Y = p.top.Y + 1;
        }
    }

    return p;
}