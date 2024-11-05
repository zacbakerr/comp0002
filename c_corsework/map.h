struct Board {
  int tilesWide;
  int tilesTall;
  int tiles[20][12];
};

int displayGrid(int tilesWide, int tilesTall);
int displayBorder(int tilesWide, int tilesTall);
int displayRobot(int x, int y, int direction);
void displayMarker(int x, int y);
void clearRobot(int x, int y, int direction);
void clearMarker(int x, int y);
void displayWall(int x, int y);

struct Board createBoard(void);