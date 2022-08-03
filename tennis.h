#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

//COURT SIZE

#define COURT_WIDTH_X 61
#define COURT_HIGHT_Y 19

//COURT DRAW
#define STARTING_POINT_X 5
#define STARTING_POINT_Y 5

#define UPPER_LEFT_CORNER 201
#define UPPER_RIGHT_CORNER 187
#define LOWER_LEFT_CORNER 200
#define LOWER_RIGHT_CORNER 188
#define VERTICAL_LINE 186
#define HORIZONTAL_LINE 205
#define UPPER_CENTER_COURT 203
#define LOWER_CENTER_COURT 202

//KEYS
#define ESC 27

//CHAR
#define EMPTY 32

#define FRAMERATE 16 //16MS IGUAL A 60FPS APROX
#define SPEED 150

void gotoXY(int, int);
void hideCursor();
void drawCourt();
void printCursor(int, int, char);
void moveCursor(int, int, int, int, char, char);


void gotoXY(int x, int y) {
    printf("%c[%d;%dH", ESC, y, x);
}

/*void gotoXY(int x, int y) {
    COORD dwPos;
    HANDLE hCon;

    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}*/

void hideCursor() {
    CONSOLE_CURSOR_INFO cci;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cci); 
}

void printCursor(int x, int y, char c) {
    printf("%c[1;%dm", ESC, 32); // color rojo (32) al caracter impreso
    gotoXY(x, y);
    
    printf("%c", c);
    printf("%c[0m", ESC); //reestablece el color por defecto de la consola
}

void drawCourt() {
    char c;
    int i, j;

    printf("%c[1;%dm", ESC, 32); // color rojo (32) al caracter impreso
    gotoXY(STARTING_POINT_X, STARTING_POINT_Y);
    
    for(i = 0; i < COURT_HIGHT_Y + 2; i++) {
        for(j = 0; j < COURT_WIDTH_X + 2; j++) {
            if (j == 0 || j == COURT_WIDTH_X + 1) {
                switch(i) {
                    case 0: c = UPPER_LEFT_CORNER * (j == 0) +
                    UPPER_RIGHT_CORNER * (j == COURT_WIDTH_X + 1);
                    break;
                    case COURT_HIGHT_Y + 1: c = LOWER_LEFT_CORNER * (j == 0) +
                    LOWER_RIGHT_CORNER * (j == COURT_WIDTH_X + 1);
                    break;
                    default: c = VERTICAL_LINE;
                    break;
                }
            }
            else {
                if(i == 0 || i == COURT_HIGHT_Y + 1) {
                    c = HORIZONTAL_LINE;
                }
                else {
                    c = ' ';
                }
            }
            printf("%c", c);
            if(j == COURT_WIDTH_X + 1) {
                gotoXY(STARTING_POINT_X, STARTING_POINT_Y + i + 1);
            }
        }
    }
    printf("%c[0m", ESC); //reestablece el color por defecto de la consola*/
}

void moveCursor(int x, int px, int y, int py, char c, char pc) {
    gotoXY(px, py);
    printf("%c", pc);
    printCursor(x, y, c);

}