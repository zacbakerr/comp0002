#include <math.h>
#include "graphics.h"

int main(void) {
  double num = (sqrt(2)/2)*50;
  drawLine(50, 30, 100, 30);
  drawLine(100, 30, 100 + num, 30 + num);
  drawLine(50, 30, 50 - num, 30 + num);
  drawLine(50 - num, 30 + num, 50 - num, 80 + num);
  drawLine(100 + num, 30 + num, 100 + num, 80 + num);
  drawLine(50 - num, 80 + num, 50, 80 + 2*num);
  drawLine(100 + num, 80 + num, 100, 80 + 2*num);
  drawLine(50, 80 + 2*num, 100, 80 + 2*num);
  return 0;
}