#include "graphics.h"
#include <math.h>

int main(void) {
  double num = 100 * (sqrt(2)/2);
  drawOval(100, 100, 200, 200);
  drawLine(200 + num, 200 + num, 200 + num, 200 - num);
  drawLine(200 + num, 200 + num, 200 - num, 200 + num);
  drawLine(200 - num, 200 - num, 200 - num, 200 + num);
  drawLine(200 - num, 200 - num, 200 + num, 200 - num);
}