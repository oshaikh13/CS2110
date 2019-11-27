#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"
 #include "images/Colorsel.h"


/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

typedef struct paintbrush {
    int row;
    int col;
    int prevRow;
    int prevCol;
    int brushsize;
    volatile u16 color;
    volatile u16 draw_color;
    volatile u16 erase_color;
} p_brush;



typedef struct bottom_banner {
    int height;
    int width;
    int row;
    int col;
}b_banner;


typedef struct {
    // Store whether or not the game is over in this member:
    volatile u16 canvas_color;
    int reset;
    p_brush* brush;
    p_brush* colorsel;
    b_banner* banner;
    int drawing;//1 is drawing, 0 is erasing
    int pressed; //1 is editing background, 0 is not editing background
    int toggle;
    unsigned short *saveArr;
    unsigned short *saveArrSmall;
    unsigned short *saveArrColorsel;
    int filter;
    int prevFilter;
} AppState;

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);
// void RE_initializeAppState(AppState* appState);
void updateBrushState(AppState* appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);
AppState *processAppStateMove (AppState *currentAppState, u32 keysPressedNow);
AppState *processAppStateSlide (AppState *currentAppState);
AppState processAppStateColorSel(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);
AppState processAppStateImageSel(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);
// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.
// void makeXO(int row, int col, int isX, XO *exo);

#endif
