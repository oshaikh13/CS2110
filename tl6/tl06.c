#include "paint2110/gba.h"

/**
 *  Draw the image with dimensions img_dimension x img_dimension at the location
 *  (x, y). You MUST use DMA as efficiently as possible.
 */
void drawSquareImage(const u16 *image, int x, int y, int img_dimension) {
    for (int row = y; row < y + img_dimension; row++) {
        DMA[3].src = &image[OFFSET(row - y, 0, img_dimension)];
        DMA[3].dst = &videoBuffer[OFFSET(row, x, WIDTH)];
        DMA[3].cnt = img_dimension | DMA_ON;
    }
}

/**
 *  Draw the image with dimensions img_dimension x img_dimension at the location
 *  (x, y), but flipped both horizontally and vertically (equivalent to rotating
 *  180 degrees). You MUST use DMA as efficiently as possible.
 */
void drawSquareImageFlippedBoth(const u16 *image, int x, int y, int img_dimension) {
    for (int row = y; row < y + img_dimension; row++) {
        DMA[3].src = &image[OFFSET((y + img_dimension - 1 - row), img_dimension - 1, img_dimension)];
        DMA[3].dst = &videoBuffer[OFFSET(row, x, WIDTH)];
        DMA[3].cnt = img_dimension | DMA_SOURCE_DECREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

/**
 *   Return a pixel with only the red value (i.e green and blue 0'd out).
 *   See the pdf for more instructions.
 */
unsigned short filterRed(unsigned short pixel) {
    return pixel & 0x1f;
}

/**
 *   Return a pixel with only the green value (i.e red and blue 0'd out).
 *   See the pdf for more instructions.
 */
unsigned short filterGreen(unsigned short pixel) {
    return pixel & (0x1f << 5);
}

/**
 *   Return a pixel with only the blue value (i.e red and green 0'd out).
 *   See the pdf for more instructions.
 */
unsigned short filterBlue(unsigned short pixel) {
    return pixel & (0x1f << 10);
}
