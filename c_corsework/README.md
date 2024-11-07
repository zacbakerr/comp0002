
# Robot Navigation Program

  

This program simulates a robot navigating through a 2D environment, avoiding obstacles and picking up markers. The robot uses a heuristic to pick its next best move to navigate efficiently through the map while avoiding collision with walls and obstacles.



## Compilation

To compile the program, run the following command in the terminal:
```bash
gcc -o runner runner.c graphics.c map.c robot.c moveSelection.c
```
Then to run it,
```bash
./runner | java -jar .\drawapp-4.0.jar
```
Ensure drawapp-4.1.jar, graphics.h, graphics.c are in the directory along with the included source code.