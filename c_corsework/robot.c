#include "robot.h"
#include "graphics.h"

void forward(struct Robot *robot) {
  if (robot->direction == 0) {
    robot->y -= 1;
  } else if (robot->direction == 90) {
    robot->x += 1;
  } else if (robot->direction == 180) {
    robot->y += 1;
  } else if (robot->direction == 270) {
    robot->x -= 1;
  }
}

void left(struct Robot *robot) {
  robot->direction -= 90;
  if (robot->direction < 0) {
    robot->direction += 360;
  }
}

void right(struct Robot *robot) {
  robot->direction += 90;
  if (robot->direction >= 360) {
    robot->direction -= 360;
  }
}

int canMoveForward(struct Robot *robot, int tilesWide, int tilesTall, int board[20][12]) {
  int newX = robot->x;
  int newY = robot->y;
  if (robot->direction == 0) {
    newY -= 1;
  } else if (robot->direction == 90) {
    newX += 1;
  } else if (robot->direction == 180) {
    newY += 1;
  } else if (robot->direction == 270) {
    newX -= 1;
  }

  if (newX < -1 || newX >= tilesWide - 1 || newY < -1 || newY >= tilesTall - 1) {
    return 0;
  }

  if (board[newY][newX] == 2) {
    return 0;
  }

  return 1;
}

int atMarker(struct Robot *robot, int board[20][12]) {
  if (robot->x < 0 || robot->y < 0) {
    return 0;
  }
  return board[robot->y][robot->x] == 1;
}

void pickUpMarker(struct Robot *robot, int board[20][12]) {
  robot->numMarkers += 1;
  board[robot->y][robot->x] = 0;
}

void dropMarker(struct Robot *robot, int board[20][12]) {
  board[robot->y][robot->x] = 1;
  robot->numMarkers -= 1;
}

int markerCount(struct Robot *robot) {
  return robot->numMarkers;
}