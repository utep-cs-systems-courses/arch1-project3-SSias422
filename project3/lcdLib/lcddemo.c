/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
j */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  int row = 0;
  int col = 0;
  int frow = 50;
  int fcol = 50;

  for(int j = 0; j<10; j++){
    drawPixel(fcol+col, frow+row, COLOR_WHITE);
    drawPixel(fcol+col, frow+10+row, COLOR_GRAY);
    row++;
  
  }
}
