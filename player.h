#include "tennis.h"

#define PLAYER 219
#define COLOR_PLAYER1 31
#define COLOR_PLAYER2 34

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
void playerMovement(player);
player controllPlayer1(int, player);
player controllPlayer2(int, player);
player controllPlayers(int, player);
player animationPlayers(int, player);


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

player controllPlayer1(int key, player p1) {
    if(key == P1_UP) {
        p1.bottom.Y = p1.bottom.Y - 1;
        p1.middle.Y = p1.middle.Y - 1;
        p1.top.Y = p1.top.Y - 1;

        return p1;
    }
    else {
        if(key == P1_DOWN) {
            p1.bottom.Y = p1.bottom.Y + 1;
            p1.middle.Y = p1.middle.Y + 1;
            p1.top.Y = p1.top.Y + 1;

            return p1;
        }
        else {
            return p1;
        }
    }
}

player controllPlayer2(int key, player p2) {
    if(key == P2_UP) {
        p2.bottom.Y = p2.bottom.Y - 1;
        p2.middle.Y = p2.middle.Y - 1;
        p2.top.Y = p2.top.Y - 1;

        return p2;
    }
    else {
        if(key == P2_DOWN) {
            p2.bottom.Y = p2.bottom.Y + 1;
            p2.middle.Y = p2.middle.Y + 1;
            p2.top.Y = p2.top.Y + 1;

            return p2;
        }
        else {
            return p2;
        }
    }
}

player controllPlayers(int key, player p) {

    if(key != 0) {
        p = controllPlayer1(key, p);
        p = controllPlayer2(key, p);

        return p;
    }
    else {
        return p;
    }
}

player animationPlayers(int key, player p) {

    if(p.middle.Y != p.middle.previous_Y) {
        p.top.previous_Y = p.top.Y;
        p.middle.previous_Y = p.middle.Y;
        p.bottom.previous_Y = p.bottom.Y;
    }

    p = controllPlayers(key,p);

    printPlayer(p);
}