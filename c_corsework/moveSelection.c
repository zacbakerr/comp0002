#include "moveSelection.h"
#include <stdlib.h>

#define HEAT_DECAY 0.8
#define HEAT_INCREASE 2.0

int isValidCell(int x, int y, int board[20][12], int width, int height) {
  if (x < 0 || x >= width || y < 0 || y >= height) return 0;
  return board[y][x] != 2;
}

void updateHeatMap(double heatMap[20][12], int width, int height) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      heatMap[y][x] *= HEAT_DECAY;
    }
  }
}

int detectBackAndForth(struct Position *history, int historySize, int x, int y) {
  if (historySize < 4) return 0;
  
  if (historySize >= 4) {
    if (history[historySize-1].x == history[historySize-3].x && history[historySize-1].y == history[historySize-3].y && history[historySize-2].x == history[historySize-4].x && history[historySize-2].y == history[historySize-4].y) {
      return 1;
    }
  }
  
  int samePositionCount = 0;
  for (int i = historySize - 1; i >= ((historySize - 8) > 0 ? (historySize - 8) : 0); i--) {
    if (history[i].x == x && history[i].y == y) {
      samePositionCount++;
      if (samePositionCount >= 3) return 1;
    }
  }
  return 0;
}

void tryAlternativeDirections(struct Robot *robot, int width, int height, int board[20][12]) {
  for (int i = 0; i < 4; i++) {
    robot->direction = (robot->direction + 90) % 360;
    if (canMoveForward(robot, width, height, board)) break;
  }
}

int calculateMoveScore(int x, int y, int direction, int currentDir, int board[20][12], int seen[20][12], int width, int height, int lastX, int lastY, int prevX, int prevY, double heatMap[20][12]) {
  int score = 0;
  if (seen[y][x] == 0) score += 2500;
  if (board[y][x] == 1) score += 3500;
  score -= (int)(heatMap[y][x] * 1500);
  
  if ((x == lastX && y == lastY) || (x == prevX && y == prevY)) {
    score -= 4000;
  }

  if (x == 0 || x == width-1 || y == 0 || y == height-1) {
    if (board[y][x] != 1) score -= 1000;
  }

  score -= seen[y][x] * 600;
  if (direction == currentDir) score += 200;
  return score;
}

int findBestDirection(struct Robot *robot, int seen[20][12], int board[20][12], int width, int height, int lastX, int lastY, int prevX, int prevY, double heatMap[20][12]) {
  const int DIRECTIONS[] = {0, 90, 180, 270};
  const int DX[] = {0, 1, 0, -1};
  const int DY[] = {-1, 0, 1, 0};
  
  int bestScore = -999999;
  int bestDir = robot->direction;
  
  for (int i = 0; i < 4; i++) {
    int newX = robot->x + DX[i];
    int newY = robot->y + DY[i];
    
    if (!isValidCell(newX, newY, board, width, height)) continue;
    
    int score = calculateMoveScore(newX, newY, DIRECTIONS[i], robot->direction, board, seen, width, height, lastX, lastY, prevX, prevY, heatMap);
    
    if (score > bestScore) {
      bestScore = score;
      bestDir = DIRECTIONS[i];
    }
  }
  return bestDir;
}

void handlePositionHistory(struct Position *history, int *historySize, struct Robot *robot) {
  if (*historySize < 100) {
    history[*historySize].x = robot->x;
    history[*historySize].y = robot->y;
    (*historySize)++;
  } else {
    for (int i = 0; i < 99; i++) {
      history[i] = history[i + 1];
    }
    history[99].x = robot->x;
    history[99].y = robot->y;
  }
}

void applyHeatToArea(double heatMap[20][12], int x, int y, int width, int height, double intensity) {
  for (int dy = -3; dy <= 3; dy++) {
    for (int dx = -3; dx <= 3; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        heatMap[ny][nx] += HEAT_INCREASE * intensity;
      }
    }
  }
}

int findDirectionAwayFromCurrent(struct Robot *robot, int width, int height, int board[20][12]) {
  int currentX = robot->x;
  int currentY = robot->y;
  int bestDistance = 0;
  int bestDir = robot->direction;
  
  for (int i = 0; i < 4; i++) {
    int testDir = i * 90;
    robot->direction = testDir;
    
    if (canMoveForward(robot, width, height, board)) {
      int newX = robot->x;
      int newY = robot->y;
      if (testDir == 0) newY--;
      else if (testDir == 90) newX++;
      else if (testDir == 180) newY++;
      else if (testDir == 270) newX--;
      
      int distance = abs(newX - currentX) + abs(newY - currentY);
      if (distance > bestDistance) {
        bestDistance = distance;
        bestDir = testDir;
      }
    }
  }
  return bestDir;
}

int calculateReturnScore(int x, int y, int direction, int currentDir, int board[20][12], int targetX, int targetY, double heatMap[20][12]) {
  int score = 0;
  int currentDist = abs(x - targetX) + abs(y - targetY);
  score -= currentDist * 1000;
  score -= (int)(heatMap[y][x] * 800);
  if (direction == currentDir) score += 100;
  return score;
}

int findReturnDirection(struct Robot *robot, int board[20][12], int width, int height, int targetX, int targetY, double heatMap[20][12]) {
  const int DIRECTIONS[] = {0, 90, 180, 270};
  const int DX[] = {0, 1, 0, -1};
  const int DY[] = {-1, 0, 1, 0};
  
  int bestScore = -999999;
  int bestDir = robot->direction;
  
  for (int i = 0; i < 4; i++) {
    int newX = robot->x + DX[i];
    int newY = robot->y + DY[i];
    
    if (!isValidCell(newX, newY, board, width, height)) continue;
    
    int score = calculateReturnScore(newX, newY, DIRECTIONS[i], robot->direction, board, targetX, targetY, heatMap);
    
    if (score > bestScore) {
      bestScore = score;
      bestDir = DIRECTIONS[i];
    }
  }
  return bestDir;
}

int isReachable(int x, int y, int board[20][12], int width, int height) {
  int visited[20][12] = {0};
  struct Position queue[240];
  int front = 0, rear = 0;
  int accessibleSpaces = 0;
  
  queue[rear].x = x;
  queue[rear].y = y;
  rear++;
  visited[y][x] = 1;
  
  while (front < rear) {
    int currentX = queue[front].x;
    int currentY = queue[front].y;
    front++;
    accessibleSpaces++;
    
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    
    for (int i = 0; i < 4; i++) {
      int newX = currentX + dx[i];
      int newY = currentY + dy[i];
      
      if (newX >= 0 && newX < width && newY >= 0 && newY < height && !visited[newY][newX] && board[newY][newX] != 2) {
        queue[rear].x = newX;
        queue[rear].y = newY;
        rear++;
        visited[newY][newX] = 1;
      }
    }
  }
  return accessibleSpaces >= 4;
}