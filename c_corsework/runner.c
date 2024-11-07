#include "map.h"
#include "graphics.h"
#include "moveSelection.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "robot.h"

#define MARKER_COUNT 5
#define WALL_COUNT 5
#define STUCK_THRESHOLD 3
#define MAX_STUCK_RECOVERY 4
#define HEAT_INCREASE 2.0

void redrawGridCell(int x, int y) {
  setColour(white);
  fillRect(110 + x * 50 + 1, 110 + y * 50 + 1, 48, 48);
  setColour(gray);
  drawRect(110 + x * 50, 110 + y * 50, 50, 50);
}

void updateRobotPosition(struct Robot *robot, struct Board *board, int seen[20][12], int width, int height, int *lastX, int *lastY, int *prevX, int *prevY, int *stuckCount, double heatMap[20][12]) {
  static struct Position history[100];
  static int historySize = 0;
  
  clearRobot(robot->x, robot->y, robot->direction);
  redrawGridCell(robot->x, robot->y);
  
  handlePositionHistory(history, &historySize, robot);
  heatMap[robot->y][robot->x] += HEAT_INCREASE;
  
  if (detectBackAndForth(history, historySize, robot->x, robot->y)) {
    applyHeatToArea(heatMap, robot->x, robot->y, width, height, 5.0);
    robot->direction = (rand() % 4) * 90;
    robot->direction = findDirectionAwayFromCurrent(robot, width, height, board->tiles);
    *stuckCount = STUCK_THRESHOLD - 1;
  }
  
  updateHeatMap(heatMap, width, height);
  
  int currentX = robot->x;
  int currentY = robot->y;
  
  if (currentX == *lastX && currentY == *lastY) {
    (*stuckCount)++;
    if (*stuckCount >= STUCK_THRESHOLD) {
      robot->direction = (robot->direction + 180) % 360;
      *stuckCount = 0;
    }
  } else {
    *stuckCount = 0;
  }
  
  robot->direction = findBestDirection(robot, seen, board->tiles, width, height, *lastX, *lastY, *prevX, *prevY, heatMap);
  
  if (!canMoveForward(robot, width, height, board->tiles)) {
    tryAlternativeDirections(robot, width, height, board->tiles);
  }
  
  if (canMoveForward(robot, width, height, board->tiles)) {
    *prevX = *lastX;
    *prevY = *lastY;
    *lastX = currentX;
    *lastY = currentY;
    forward(robot);
  }
  
  displayRobot(robot->x, robot->y, robot->direction);
}

void processMarkerCollection(struct Robot *robot, struct Board *board, int markerLocations[20][12]) {
  if (atMarker(robot, board->tiles) && markerLocations[robot->y][robot->x]) {
    pickUpMarker(robot, board->tiles);
    markerLocations[robot->y][robot->x] = 0;
    clearMarker(robot->x, robot->y);
    redrawGridCell(robot->x, robot->y);
  }
}

int main(void) {
  srand(time(NULL));

  struct Board board = createBoard();
  int tilesWidth = board.tilesWide;
  int tilesHeight = board.tilesTall;
  int seen[20][12] = {0};
  int markerLocations[20][12] = {0};
  double heatMap[20][12] = {0};
  
  setWindowSize(200 + tilesWidth * 50, 200 + tilesHeight * 50);
  displayBorder(tilesWidth, tilesHeight);
  displayGrid(tilesWidth, tilesHeight);

  for (int i = 0; i < WALL_COUNT; i++) {
    int wx = rand() % (tilesWidth - 2) + 1;
    int wy = rand() % (tilesHeight - 2) + 1;
    if (board.tiles[wy][wx] == 0) {
      board.tiles[wy][wx] = 2;
      displayWall(wx, wy);
    }
  }

  for (int i = 0; i < MARKER_COUNT; i++) {
    int mx, my;
    int attempts = 0;
    const int MAX_ATTEMPTS = 100;
    
    do {
      mx = rand() % (tilesWidth - 2) + 1;
      my = rand() % (tilesHeight - 2) + 1;
      attempts++;
      
      if (attempts >= MAX_ATTEMPTS) {
        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = mx + dx;
            int ny = my + dy;
            if (nx >= 0 && nx < tilesWidth && ny >= 0 && ny < tilesHeight) {
              if (board.tiles[ny][nx] == 2) {
                board.tiles[ny][nx] = 0;
                redrawGridCell(nx, ny);
              }
            }
          }
        }
        break;
      }
    } while (board.tiles[my][mx] != 0 || !isReachable(mx, my, board.tiles, tilesWidth, tilesHeight));
    
    board.tiles[my][mx] = 1;
    markerLocations[my][mx] = 1;
    displayMarker(mx, my);
  }

  struct Robot robot;
  do {
    robot.x = rand() % (tilesWidth - 2) + 1;
    robot.y = rand() % (tilesHeight - 2) + 1;
  } while (board.tiles[robot.y][robot.x] == 2);
  
  int startX = robot.x;
  int startY = robot.y;
  robot.direction = 0;
  robot.numMarkers = 0;
  displayRobot(robot.x, robot.y, robot.direction);

  int lastX = -1, lastY = -1;
  int prevX = -1, prevY = -1;
  int stuckCount = 0;

  while (robot.numMarkers < MARKER_COUNT) {
    processMarkerCollection(&robot, &board, markerLocations);
    updateRobotPosition(&robot, &board, seen, tilesWidth, tilesHeight,
                       &lastX, &lastY, &prevX, &prevY, &stuckCount, heatMap);
    seen[robot.y][robot.x]++;
    sleep(50);
  }

  for (int i = 0; i < tilesHeight; i++) {
    for (int j = 0; j < tilesWidth; j++) {
      seen[i][j] = 0;
      heatMap[i][j] = 0;
    }
  }

  while (robot.x != startX || robot.y != startY) {
    clearRobot(robot.x, robot.y, robot.direction);
    redrawGridCell(robot.x, robot.y);
    
    heatMap[robot.y][robot.x] += HEAT_INCREASE;
    updateHeatMap(heatMap, tilesWidth, tilesHeight);
    
    robot.direction = findReturnDirection(&robot, board.tiles, tilesWidth, tilesHeight, startX, startY, heatMap);
    
    if (!canMoveForward(&robot, tilesWidth, tilesHeight, board.tiles)) {
      tryAlternativeDirections(&robot, tilesWidth, tilesHeight, board.tiles);
    }
    
    if (canMoveForward(&robot, tilesWidth, tilesHeight, board.tiles)) {
      forward(&robot);
    }
    
    displayRobot(robot.x, robot.y, robot.direction);
    sleep(50);
  }

  while (robot.numMarkers > 0) {
    dropMarker(&robot, board.tiles);
    displayMarker(robot.x, robot.y);
    sleep(200);
  }

  return 0;
}