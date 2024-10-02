#include "graphics.h"

int main() {
  drawOval(100, 100, 10, 50);
  setColour(red);
  drawOval(100, 100, 50, 10);
  setColour(orange);
  drawOval(50, 100, 50, 10);
  setColour(green);
  drawOval(100, 50, 10, 50);
  setColour(magenta);
  drawOval(200, 200, 10, 50);
  setColour(green);
  drawOval(200, 200, 50, 10);
  setColour(blue);
  drawOval(150, 200, 50, 10);
  return 0;
}