#ifndef ROBOT_H
#define ROBOT_H

struct Robot
{
  int x;
  int y;
  int direction;
  int numMarkers;
};

void forward(struct Robot *robot);
void left(struct Robot *robot);
void right(struct Robot *robot);
int canMoveForward(struct Robot *robot, int tilesWide, int tilesTall, int board[20][12]);
int atMarker(struct Robot *robot, int board[20][12]);
void pickUpMarker(struct Robot *robot, int board[20][12]);
void dropMarker(struct Robot *robot, int board[20][12]);
int markerCount(struct Robot *robot);

#endif