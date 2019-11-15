#include <stdio.h>
#include <stdlib.h>
#include "gba.h"
#include "game.h"
#include "images/garbage.h"
#include "images/window.h"
#include "images/swatter.h"
#include "images/startScreen.h"
// #include "images/loseScreen.h"
// #include "images/winScreen.h"

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
} Fly;

int deltas[] = {-3, -2, -1, 1, 2, 3};

struct Fly flies[5];
int attempts = 0;
int ndelta = 6;

void moveSwatter(Swatter* p, int s);
void drawPlayer(Swatter* p);
void undrawPlayer(Swatter* p, int s);
void initFlies(void);
void updateFlies(void);
void drawFlies(void);


// void undraw(Swatter* p, int s) {

// 	int x = p->x;
// 	int y = p->y;
//   int w = p->w;
//   int h = p->h;

//   if(KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
//     drawImagePortionDMA(x + w, y, s, h, window);   
//   }
  
//   if(KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
//     drawImagePortionDMA(x - s, y, s, h, window);
//   }

// 	if(KEY_DOWN(BUTTON_UP, BUTTONS)) {
// 		drawImagePortionDMA(x, y + h, w, s, window);
// 	}

// 	if(KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
// 		drawImagePortionDMA(x, y - s, w, s, window);
// 	}
// }

void undraw(Swatter* p) {

	int x = p->x;
	int y = p->y;
  int w = p->w;
  int h = p->h;
  drawImagePortionDMA(x, y, w, h, window);
}

void moveSwatter(Swatter* p, int s) {

  undraw(p);
  if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && p->x > 0) {
    p->x = p->x - s;
  } 
  if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) && p->x + p->w + s < WIDTH) {
    p->x = p->x + s; 
  }
  if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && p->y + p->h < HEIGHT) {
    p->y = p->y + s; 
  }
  if (KEY_DOWN(BUTTON_UP, BUTTONS) && p->y > 0) {
    p->y = p->y - s;
  }
  drawPlayer(p);
  // undraw(p, s);
}

void drawFlies(void) {
  for (int i = 0; i < 5; i++) {
    drawRectDMA(flies[i].x, flies[i].y, flies[i].w, flies[i].h, RED);
  }

}

void initFlies(void) {
  for (int i = 0; i < 5; i++) {
    flies[i].x = randint(0, WIDTH);
    flies[i].y = randint(0, HEIGHT);
    flies[i].w = 10;
    flies[i].h = 10;
    flies[i].dy = deltas[randint(0, ndelta)];
    flies[i].dx = deltas[randint(0, ndelta)];
  }
}


void updateFlies(void) {
  for(int i=0; i < 5; i++) {
    drawImagePortionDMA(flies[i].x, flies[i].y, flies[i].w, flies[i].h, window);

    flies[i].x = flies[i].x + flies[i].dx;
    flies[i].y = flies[i].y + flies[i].dy;

    if (flies[i].x >= WIDTH-flies[i].w) { // right
      flies[i].x = WIDTH-flies[i].w;
      flies[i].dx = -flies[i].dx;
    }

    if (flies[i].y >= HEIGHT-flies[i].h) { 
      // bottom
      flies[i].y = HEIGHT-flies[i].h;
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

void drawPlayer(Swatter* p) {
	drawImageDMA(p->x, p->y, p->w, p->h, swatter);
  // drawRectDMA(p->x, p->y, p->width, p->height, RED);
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

  Swatter playerSwatter = {0, 0, 20, 20};
  Swatter *p = &playerSwatter;
  drawFullScreenImageDMA(startScreen);

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons


    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    waitForVBlank();

    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      initFlies();
      drawFullScreenImageDMA(startScreen);
      p->x = 0;
      p->y = 0;
      state = START;
    }

    switch(state) {
      case START:
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          drawFullScreenImageDMA(window);
          state = PLAY;
        }
        break;
      case PLAY:
        updateFlies();
        moveSwatter(p, 3);
        // state = ?
        break;
      case WIN:

        // state = ?
        break;
      case LOSE:
    
        // state = ?
        break;
    }


    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
