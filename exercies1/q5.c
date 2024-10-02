#include "graphics.h"

int main(void) {
  drawLine(30, 30, 120, 30);
  drawLine(30, 30, 30, 80);
  drawLine(30, 80, 120, 80);
  drawLine(120, 80, 120, 30);
  drawRect(150, 150, 60, 140);
  return 0;
}