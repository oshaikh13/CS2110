#ifndef __TL06_H__
#define __TL06_H__

void drawSquareImage(const u16 *, int, int, int);
void drawSquareImageFlippedBoth(const u16 *, int, int, int);
unsigned short filterRed(unsigned short pixel);
unsigned short filterBlue(unsigned short pixel);
unsigned short filterGreen(unsigned short pixel);

#endif
