#include <stdio.h>
#include <stdlib.h>
#include "gba.h"
#include "game.h"
#include "images/garbage.h"
#include "images/window.h"
#include "images/swatter.h"
#include "images/flyImg.h"
#include "images/startScreen.h"
#include "images/loseScreen.h"
#include "images/winScreen.h"

                    /* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"


                    /* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  PLAY,
  WIN,
  LOSE,
} GBAState;

typedef struct Swatter {
  int x;
  int y;
  int w;
  int h;
} Swatter;

typedef struct Fly {
 int x;
 int y;
 int dy;
 int dx;
 int w;
 int h;
 int visible; 
} Fly;


struct Fly flies[5];
int numVisible = 5;
int clockCycle = 0;
int showSwatted = 0;
Swatter playerSwatter = {0, 0, 20, 20};
Swatter *p = &playerSwatter;

void moveSwatter(Swatter* p, int s, u32 currentButtons, u32 previousButtons);
void drawPlayer(Swatter* p, u32 currentButtons, u32 previousButtons);
void undrawPlayer(Swatter* p, int s);
void initFlies(void);
void updateFlies(int clockCycle);
void drawFlies(void);
void resetState(void);
void printScore(void);
int checkCollisionAndRespawn(Swatter* p, u32 currentButtons, u32 previousButtons, int clockCycle);


void undraw(Swatter* p) {

	int x = p->x;
	int y = p->y;
  int w = p->w;
  int h = p->h;
  drawImagePortionDMA(x, y, w, h, window);
}

void moveSwatter(Swatter* p, int s, u32 currentButtons, u32 previousButtons) {

  undraw(p);
  if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && p->x > 0) {
    p->x = p->x - s;
  }

  if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) && p->x + p->w + s < WIDTH) {
    p->x = p->x + s; 
  }

  if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && p->y + p->h + 8 < HEIGHT) {
    p->y = p->y + s; 
  }

  if (KEY_DOWN(BUTTON_UP, BUTTONS) && p->y > 0) {
    p->y = p->y - s;
  }
  drawPlayer(p, currentButtons, previousButtons);
  // undraw(p, s);
}

void drawFlies(void) {
  for (int i = 0; i < 5; i++) {
    if (flies[i].visible) {
      drawImageDMA(flies[i].x, flies[i].y, flies[i].w, flies[i].h, fly);
    }
  }

}

void initFlies(void) {
  numVisible = 5;
  for (int i = 0; i < 5; i++) {
    flies[i].x = randint(0, WIDTH);
    flies[i].y = randint(0, HEIGHT);
    flies[i].w = 10;
    flies[i].h = 10;
    flies[i].visible = 1;
    flies[i].dy = 1;
    flies[i].dx = 1;
  }

  for (int i = 0; i < 2; i++) {
    numVisible--;
    flies[i].visible = 0;
  }

}

int checkCollisionAndRespawn(Swatter *p, u32 currentButtons, u32 previousButtons, int clockCycle) {
  int madeVisible = 0;
  for (int i = 0; i < 5; i++) {

    if (clockCycle % 600 == 0) {
      if (!flies[i].visible && !madeVisible) {
        numVisible++;
        printScore();
        madeVisible = 1;
        flies[i].visible = 1;
      }
    }

    if (flies[i].x >= p->x && p->x + p->w >= flies[i].x && 
        flies[i].y >= p->y && flies[i].y <= p->y + p->h && flies[i].visible &&
        KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons) && showSwatted == 0) {
      numVisible--;
      printScore();
      flies[i].visible = 0;
      return 1;
    }

  }
  return 0;
}

void updateFlies(int clockCycle) {
  for(int i=0; i < 5; i++) {
    drawImagePortionDMA(flies[i].x, flies[i].y, flies[i].w, flies[i].h, window);

    if (clockCycle % 50 == 0) {
      int tempDx = randint(0, 2);
      int tempDy = randint(0, 2);

      if (tempDx == 0) {
        flies[i].dx = -1;
      } else {
        flies[i].dx = 1;
      }

      if (tempDy == 0) {
        flies[i].dy = -1;
      } else {
        flies[i].dy = 1;
      }
    }

    flies[i].x = flies[i].x + flies[i].dx;
    flies[i].y = flies[i].y + flies[i].dy;

    if (flies[i].x >= WIDTH-flies[i].w) { // right
      flies[i].x = WIDTH-flies[i].w;
      flies[i].dx = -flies[i].dx;
    }

    if (flies[i].y >= HEIGHT-flies[i].h - 8) { 
      // bottom
      flies[i].y = HEIGHT-flies[i].h - 8;
      flies[i].dy = -flies[i].dy;
    }
    
    if (flies[i].x < 0) { 
      // left
      flies[i].x = 0;
      flies[i].dx = -flies[i].dx;
    }

    if (flies[i].y < 0) { // top
      flies[i].y = 0;
      flies[i].dy = -flies[i].dy;
    }

  }
  drawFlies();
}

int swatCntr = 0;
void drawPlayer(Swatter* p, u32 currentButtons, u32 previousButtons) {
  swatCntr++;
  if (swatCntr > 10 && showSwatted == 1) {
    showSwatted = 0;
    swatCntr = 0;
  }

  if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
    showSwatted = 1;
    swatCntr = 0;
  }

  if (showSwatted) {
    drawRectDMA(p->x, p->y, p->w, p->h, BLACK);
  } else {
    drawImageDMA(p->x, p->y, p->w, p->h, swatter);
  }
}

void resetState(void) {
  initFlies();
  p->x = 0;
  p->y = 0;
}

void printScore(void) {
  char temp[50];
  drawImagePortionDMA(0, HEIGHT - 10, 100, 10, window);
	sprintf(temp, "FLIES LEFT: %d", numVisible);
  drawString(2, HEIGHT - 8, temp, BLACK);
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  initFlies();
  waitForVBlank();


  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state
  GBAState state = START;

  drawFullScreenImageDMA(startScreen);

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons


    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    waitForVBlank();

    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      resetState();
      drawFullScreenImageDMA(startScreen);
      state = START;
    }

    switch(state) {
      case START:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          drawFullScreenImageDMA(window);
          printScore();
          state = PLAY;
        }
        break;
      case PLAY:
        updateFlies(clockCycle);
        checkCollisionAndRespawn(p, currentButtons, previousButtons, clockCycle);
        moveSwatter(p, 3, currentButtons, previousButtons);

        if (numVisible == 5) {
          resetState();
          drawFullScreenImageDMA(loseScreen);
          state = LOSE;
        }

        if (numVisible == 0) {
          resetState();
          drawFullScreenImageDMA(winScreen);
          state = WIN;
        }

        // state = ?
        break;
      case WIN:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          drawFullScreenImageDMA(window);
          printScore();
          state = PLAY;
        }
        // state = ?
        break;
      case LOSE:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          drawFullScreenImageDMA(window);
          printScore();
          state = PLAY;
        }
        // state = ?
        break;
    }

    clockCycle++;
    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
