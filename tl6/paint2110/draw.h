#ifndef DRAW_H
#define DRAW_H

#include "logic.h"

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state);

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state);

void drawLine(AppState *state);
void drawAppStateColorSel(AppState *state);
void fullDrawAppStateColorSel(AppState *state);
void restoreAppState(AppState *state);
void fullDrawAppStateImageSel(AppState *state);
void drawAppStateImageSel(AppState *state);
void restoreAppStateImage(AppState *state);

// If you have anything else you need accessible from outside the graphics.c
// file, you can add them here. You likely won't.

// void drawWinState(AppState *state);

#endif
