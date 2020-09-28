#pragma once
#include<iostream>
#include<string>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

#define DOOR_COLOR YELLOW
#define WALL_COLOR MAGENTA
#define PRIZE_COLOR GREEN

// static void setCursorCoord(int column, int row);
extern void setCursorCoord(const int column, const int row);

class Room
{
private:
	bool _doors[4];// holds boolean for which walls are doors. 0 - wall, 1- door
					// 0 - top wall, 1 - right wall, 2 - left wall, 3 - bottom wall
	int _treasure; // holds the amount of treasure in the room. 0 - room with no treasure
	bool _outerRoom;// type of room. 0 - inner room, 1 - outer room

public:
	Room();
	Room(const bool arr1[4], const int treasure, const bool outerRoom);
	Room(const int wall0, const int wall1, const int wall2, const int wall3);
	//~Room(); // dont need a destructor because no memory allocations were created

	bool getDoors(int i) const;
	const bool *getDoors() const;
	void setDoors(const bool wall0, const bool wall1, const bool wall2, const bool wall3);
	void setDoors(const bool arr[4]);
	void toggleDoors(const int wallNum); // toggles a single door
	void toggleDoors(const bool arr[4]); // toggle all selected doors
	void setTreasure(const int tres);
	int getTreasure() const { return _treasure; }
	void setOuterRoom(bool outerRoom) { _outerRoom = outerRoom; }
	bool getOuterRoom() const { return _outerRoom; }
	void print(const int x, const int y) const;
		
private:
	void printTop() const;
	void printBottom() const;
	void printSides(const int side) const;

};

