#include "Room.h"

bool Room::getDoors(int i) const
{
	if (i < 0 || i > 3) throw "Invalid wall number";
	return _doors[i];
}

const bool *Room::getDoors() const
{
	return _doors;
}

void Room::setDoors(const bool wall0, const bool wall1, const bool wall2, const bool wall3)
{
	this->_doors[0] = wall0;
	this->_doors[1] = wall1;
	this->_doors[2] = wall2;
	this->_doors[3] = wall3;
}

void Room::setDoors(const bool arr[4])
{
	for (int i = 0; i < 4; i++)
		this->_doors[i] = arr[i];
}

// change a door to a wall
void Room::toggleDoors(const int wallNum)
{
	if (wallNum < 0 || wallNum > 3) throw "Invalid wall number";
	this->_doors[wallNum] = 1;
}

void Room::toggleDoors(const bool arr[4])
{
	for (int i = 0; i < 4; i++)
		if (arr[i] == 1)
			this->_doors[i] = arr[i];
}

void Room::setTreasure(const int tres)
{
	if (tres < 0) throw "Negative treasure value set";
	_treasure = tres; 
}

void Room::print(const int x,const  int y) const
{
	setCursorCoord(x, y);
	printTop();
	setCursorCoord(x, y + 1);
	printSides(1);
	setCursorCoord(x+4, y + 1);
	printSides(2);
	setCursorCoord(x, y + 2);
	printBottom();
	if (this->_treasure)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, PRIZE_COLOR);
		setCursorCoord(x + 1, y + 1);
		wcout << this->_treasure << "$";
	}
}

void Room::printTop() const
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_doors[0] == true) {
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"┌";
		SetConsoleTextAttribute(h, DOOR_COLOR);
		wcout << L"▀▀▀";
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"┐\n";
	}
	else {
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"┌───┐\n";
	}
}

void Room::printSides(const int side) const
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (side == 1) {
		if (_doors[3] == true)
		{
			SetConsoleTextAttribute(h, DOOR_COLOR);
			wcout << L"▌";
		}
		else
		{
			SetConsoleTextAttribute(h, WALL_COLOR);
			wcout << L"|";
		}
	}

	if (side == 2) {
		if (_doors[1] == true)
		{
			SetConsoleTextAttribute(h, DOOR_COLOR);
			wcout << L"▐\n";
		}
		else
		{
			SetConsoleTextAttribute(h, WALL_COLOR);
			wcout << L"|\n";
		}
	}
}

void Room::printBottom() const
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_doors[2] == true)
	{
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"└";
		SetConsoleTextAttribute(h, DOOR_COLOR);
		//wcout << L"═══";
		wcout << L"▄▄▄";
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"┘\n";
	}
	else
	{
		SetConsoleTextAttribute(h, WALL_COLOR);
		wcout << L"└───┘\n";
	}
	SetConsoleTextAttribute(h, 15);
}

Room::Room()
{
	this->setDoors(0, 0, 0, 0);
	this->setTreasure(0);
	this->setOuterRoom(0);
}

Room::Room(const int wall0, const int wall1, const int wall2, const int wall3)
{
	this->setDoors(wall0, wall1, wall2, wall3);
	this->setTreasure(0);
	this->setOuterRoom(0);
}

Room::Room(const bool arr1[4], const int treasure, const bool outerRoom)
{
	this->setDoors(arr1);
	this->setTreasure(treasure);
	this->setOuterRoom(outerRoom);
}

extern void setCursorCoord(const int column, const int row)
{
	COORD coord;
	coord.X = column;
	coord.Y = row;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}