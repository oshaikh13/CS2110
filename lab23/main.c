#include "lib.h"
#include "panda_tl.h"
#include "panda_tr.h"
#include "panda_br.h"
#include "panda_bl.h"

void drawImageFlippedUD(int row, int col, int width, int height, const u16 *image) {
    // TODO: Implement this function that draws the image, but flipped upside-down. You MUST use DMA!

    for (int r = row; r < row + height; r++) {
        DMA[3].src = &image[OFFSET((row + height - 1)  - (r - row), 0, width)];
        DMA[3].dst = &videoBuffer[OFFSET(r, col, WIDTH)];
        DMA[3].cnt = width | DMA_ON;
    }
    
}

void drawImageFlippedLR(int row, int col, int width, int height, const u16 *image) {
    // TODO: Implement this function that draws the image, but flipped left-right. You MUST use DMA!

    for (int r = row; r < row + height; r++) {
        DMA[3].src = image + OFFSET(r - row, width - 1, width);
        DMA[3].dst = videoBuffer + OFFSET(r, col, WIDTH);
        DMA[3].cnt = width | DMA_SOURCE_DECREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }

}

void drawImage(int row, int col, int width, int height, const u16 *image) {
    for (int r = row; r < row + height; r++) {
        DMA[3].src = image + OFFSET(r - row, 0, width);
        DMA[3].dst = videoBuffer + OFFSET(r, col, WIDTH);
        DMA[3].cnt = width | DMA_ON;
    }
}


int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;


                           /* TODO */
        /* Oh no! The panda isn't being drawn correctly. */

    /* Change these first two to call your drawImageFlippedUD() function instead of drawImage */
    drawImageFlippedUD(0, 0, 120, 80, panda_tl);
    drawImageFlippedUD(0, 120, 120, 80, panda_tr);

    /* And these two to call your drawImageFlippedLR() function instead of drawImage */
    drawImageFlippedLR(80, 0, 120, 80, panda_bl);
    drawImageFlippedLR(80, 120, 120, 80, panda_br);

    while(1) {

    }
}
