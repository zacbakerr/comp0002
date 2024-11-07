#include "graphics.h"
#include "robot.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void displayGrid(int tilesWide, int tilesTall) {
  setColour(gray);
  for (int i = 1; i < tilesWide + 1; i++) {
    for (int k = 1; k < tilesTall + 1; k++) {
      drawRect(i*50 + 10, k*50 + 10, 50, 50);
    }
  }
}

void displayBorder(int tilesWide, int tilesTall) {
  setColour(red);
  fillRect(20, 20, 50 * (tilesWide+1), 40);
  fillRect(20, 20, 40, 50 * (tilesTall+1));
  fillRect(50 * (tilesWide+1) + 10, 20, 40, 50 * (tilesTall+1) + 30);
  fillRect(20, 50 * (tilesTall+1) + 10, 50 * (tilesWide+1), 40);
}

void displayRobot(int x, int y, int direction) {
  x = 135 + (x) * 50;
  y = 110 + (y) * 50;
  setColour(green);
  if (direction == 180) {
    int x_coords[] = {x, x + 24, x - 24};
    int y_coords[] = {y + 48, y + 1, y + 1};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 0) {
    int x_coords[] = {x, x + 24, x - 24};
    int y_coords[] = {y, y + 49, y + 49};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 90) {
    int x_coords[] = {x-24, x + 24, x - 24};
    int y_coords[] = {y, y + 24, y + 49};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 270) {
    int x_coords[] = {x+24, x + 24, x-24};
    int y_coords[] = {y, y + 49, y+24};
    fillPolygon(3, x_coords, y_coords);
  }
}

void clearRobot(int x, int y, int direction) {
  x = 135 + (x) * 50;
  y = 110 + (y) * 50;
  setColour(white);
  if (direction == 180) {
    int x_coords[] = {x, x + 24, x - 24};
    int y_coords[] = {y + 48, y + 1, y + 1};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 0) {
    int x_coords[] = {x, x + 24, x - 24};
    int y_coords[] = {y, y + 49, y + 49};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 90) {
    int x_coords[] = {x-24, x + 24, x - 24};
    int y_coords[] = {y, y + 24, y + 49};
    fillPolygon(3, x_coords, y_coords);
  } else if (direction == 270) {
    int x_coords[] = {x+24, x + 24, x-24};
    int y_coords[] = {y, y + 49, y+24};
    fillPolygon(3, x_coords, y_coords);
  }
}

void displayMarker(int x, int y) {
  x = 110 + (x) * 50;
  y = 110 + (y) * 50;
  setColour(gray);
  fillRect(x, y, 50, 50);
}

void clearMarker(int x, int y) {
  x = 110 + (x) * 50;
  y = 110 + (y) * 50;
  setColour(white);
  fillRect(x+1, y+1, 48, 48);
}

void displayWall(int x, int y) {
  x = 110 + (x) * 50;
  y = 110 + (y) * 50;
  setColour(black);
  fillRect(x+1, y+1, 48, 48);
}

struct Board {
  int tilesWide;
  int tilesTall;
  int tiles[20][12];
};

struct Board createBoard(void) {
  int tilesWide = rand() % 15 + 6;
  int tilesTall = rand() % 9 + 4;

  struct Board board;
  board.tilesWide = tilesWide;
  board.tilesTall = tilesTall;

  // 0 = empty, 1 = marker, 2 = wall, 3 = robot
  for (int i = 0; i < tilesTall; i++) {
    for (int k = 0; k < tilesWide; k++) {
      board.tiles[i][k] = 0;
    }
  }

  return board;
}