#include <math.h>
#include "graphics.h"

int main(void) {
  double sinang = 0.900968868 * 50;
  double cosang = 0.433883739 * 50;
  // drawLine(50, 30, 100, 30);
  drawLine(100, 30, 100 + sinang, 30 + cosang);
  drawLine(100, 30, 100 - sinang, 30 + cosang);
  drawLine(100 + sinang, 30 + cosang, 100 + sinang + cosang, 30 + cosang + sinang);
  drawLine(100 - sinang, 30 + cosang, 100 - sinang - cosang, 30 + cosang + sinang);
  drawLine(100 + sinang + cosang, 30 + cosang + sinang, 100 + sinang - cosang, 30 + cosang + sinang + sinang);
  drawLine(100 - sinang - cosang, 30 + cosang + sinang, 100 - sinang + cosang, 30 + cosang + sinang + sinang);
  drawLine(100 + sinang - cosang, 30 + cosang + sinang + sinang, 100 - sinang + cosang, 30 + cosang + sinang + sinang);
}