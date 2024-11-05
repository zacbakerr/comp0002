#include "map.h"
#include "graphics.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "robot.h"

struct Marker {
  int x;
  int y;
};

struct Wall {
  int x;
  int y;
};

int pickDirection(int seen[20][12], struct Robot robot) {
  int option1 = seen[robot.y][robot.x - 1];
  int option2 = seen[robot.y][robot.x + 1];
  int option3 = seen[robot.y - 1][robot.x];
  int option4 = seen[robot.y + 1][robot.x];

  // find the lowest value
  int lowest = option1;
  int direction = 270;
  if (option2 < lowest) {
    lowest = option2;
    direction = 90;
  }
  if (option3 < lowest) {
    lowest = option3;
    direction = 0;
  }
  if (option4 < lowest) {
    lowest = option4;
    direction = 180;
  }

  return direction;
}

int main(void) {
  srand(time(NULL));

  struct Board board = createBoard();
  int tilesWidth = board.tilesWide;
  int tilesHeight = board.tilesTall;

  int seen[20][12];
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 12; j++) {
      seen[i][j] = 0;
    }
  }

  int lastX = 0;
  int lastY = 0;

  setWindowSize(200 + tilesWidth * 50, 200 + tilesHeight * 50);
  displayBorder(tilesWidth, tilesHeight);
  displayGrid(tilesWidth, tilesHeight);

  struct Wall walls[7];
  struct Marker markers[7];

  for (int i = 0; i < rand() % 7 + 1; i++) {
    walls[i].x = rand() % (tilesWidth - 1);
    walls[i].y = rand() % (tilesHeight - 1);
    board.tiles[walls[i].y][walls[i].x] = 2;
    displayWall(walls[i].x, walls[i].y);
  }

  int numMarkers = rand() % 7 + 1;
  printf("Number of markers: %d\n", numMarkers);
  for (int i = 0; i < numMarkers; i++) {
    markers[i].x = rand() % (tilesWidth - 3) + 1;
    markers[i].y = rand() % (tilesHeight - 3) + 1;
    printf("Marker %d at (%d, %d)\n", i + 1, markers[i].x, markers[i].y);
    board.tiles[markers[i].y][markers[i].x] = 1;
    displayMarker(markers[i].x, markers[i].y);
  }

  struct Robot robot;
  robot.x = rand() % (tilesWidth - 1);
  robot.y = rand() % (tilesHeight - 1);
  robot.direction = (rand() % 4) * 90;
  robot.numMarkers = 0;
  displayRobot(robot.x, robot.y, robot.direction);

  // Robot movement loop
  while (markerCount(&robot) < numMarkers) {
    while (canMoveForward(&robot, tilesWidth, tilesHeight, board.tiles)) {
      sleep(50);
      if (atMarker(&robot, board.tiles)) {
        pickUpMarker(&robot, board.tiles);
        clearMarker(robot.x, robot.y);
      }
      clearRobot(robot.x, robot.y, robot.direction);
      int oldDirection = robot.direction;

      if (robot.direction == 0) {
        if (seen[robot.y - 1][robot.x] > 1 && robot.y < tilesHeight - 1) {
          robot.direction = pickDirection(seen, robot);
        }
      } else if (robot.direction == 90) {
        if (seen[robot.y][robot.x + 1] > 1 && robot.x > 1) {
          robot.direction = pickDirection(seen, robot);
        }
      } else if (robot.direction == 180) {
        if (seen[robot.y + 1][robot.x] > 1 && robot.y > 1) {
          robot.direction = pickDirection(seen, robot);
        }
      } else if (robot.direction == 270) {
        if (seen[robot.y][robot.x - 1] > 1 && robot.x < tilesWidth - 2) {
          robot.direction = pickDirection(seen, robot);
        }
      }

      while (!canMoveForward(&robot, tilesWidth, tilesHeight, board.tiles)) {
        robot.direction = (robot.direction + 90) % 360;
      }

      if (robot.direction + 180 == oldDirection) {
        robot.direction = (robot.direction + 90) % 360;
      } else if (robot.direction - 180 == oldDirection) {
        robot.direction = (robot.direction + 90) % 360;
      }

      forward(&robot);
      displayRobot(robot.x, robot.y, robot.direction);
      seen[robot.y][robot.x] += 1;
    }
    sleep(50);
    clearRobot(robot.x, robot.y, robot.direction);
    if (seen[robot.y][robot.x] == 0) {
      robot.direction = (robot.direction + 90) % 360;
    } else if (seen[robot.y][robot.x] == 1) {
      robot.direction = (robot.direction + 270) % 360;
    } else if (seen[robot.y][robot.x] == 2) {
      robot.direction = (robot.direction + 180) % 360;
    } else if (seen[robot.y][robot.x] == 3) {
      robot.direction = (robot.direction + 270) % 360;
    } else if (seen[robot.y][robot.x] % 10 == 0) {
      robot.direction = (robot.direction + 180) % 360;
    } else if (seen[robot.y][robot.x] % 11 == 0) {
      robot.direction = (robot.direction + 180) % 360;
    } else if (seen[robot.y][robot.x] % 2 == 0) {
      robot.direction = (robot.direction + 90) % 360;
    } else {
      robot.direction = (robot.direction + 270) % 360;
    }

    displayRobot(robot.x, robot.y, robot.direction);
    seen[robot.y][robot.x] += 1;
  }

  return 0;
}