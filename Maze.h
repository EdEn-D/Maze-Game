#pragma once
#include "Room.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_TRESURES 3
#define MAZE_SIZE 10

#define TEXT_AXIS (MAZE_SIZE * 5) + 5

extern bool inBounds(const int x, const int y);

class Maze
{
private:
    int _tresCount = 0;
    int _tresures[MAX_TRESURES];
    Room _rooms[MAZE_SIZE][MAZE_SIZE];

public:
    void setTresCount(int count) { _tresCount = count; }
    int getTresCount() const { return _tresCount; }

    Maze();
    Maze(const int tresCount);
    void printMaze() const;
    int getGoldRoom(const int i) const;
    Room getRoom(int const x, int const y) const;

private:
    void setStartPoint();
    void plantGold(const int count);
    void buildGoldPaths(const int count);
    void randomizeRooms();
    void fixSingleDoors(const int x, const int y);
};