#ifndef MOVE_SELECTION_H
#define MOVE_SELECTION_H

#include "robot.h"
#include "map.h"

struct Position {
  int x;
  int y;
};

int isValidCell(int x, int y, int board[20][12], int width, int height);
int isReachable(int x, int y, int board[20][12], int width, int height);
int calculateMoveScore(int x, int y, int direction, int currentDir, int board[20][12], 
                      int seen[20][12], int width, int height, int lastX, int lastY, 
                      int prevX, int prevY, double heatMap[20][12]);
int findBestDirection(struct Robot *robot, int seen[20][12], int board[20][12], 
                     int width, int height, int lastX, int lastY, int prevX, int prevY, 
                     double heatMap[20][12]);
int calculateReturnScore(int x, int y, int direction, int currentDir, int board[20][12], 
                        int targetX, int targetY, double heatMap[20][12]);
int findReturnDirection(struct Robot *robot, int board[20][12], int width, int height, 
                       int targetX, int targetY, double heatMap[20][12]);
void updateHeatMap(double heatMap[20][12], int width, int height);
void applyHeatToArea(double heatMap[20][12], int x, int y, int width, int height, double intensity);
int findDirectionAwayFromCurrent(struct Robot *robot, int width, int height, int board[20][12]);
void tryAlternativeDirections(struct Robot *robot, int width, int height, int board[20][12]);
int detectBackAndForth(struct Position *history, int historySize, int x, int y);
void handlePositionHistory(struct Position *history, int *historySize, struct Robot *robot);

#endif 