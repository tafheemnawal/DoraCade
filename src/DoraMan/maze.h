#ifndef MAZE_H
#define MAZE_H

#define MAZE_ROWS 10
#define MAZE_COLS 16
#define TILE_SIZE 60

void DrawMaze(void);
int IsWall(int row, int col);

#endif