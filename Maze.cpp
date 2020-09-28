#include "Maze.h"

Maze::Maze()
{
	setTresCount(0);
	setStartPoint();
}

Maze::Maze(const int tresCount)
{
	setTresCount(tresCount);
	setStartPoint();
	plantGold(tresCount);
	buildGoldPaths(tresCount);
	randomizeRooms();
}

void Maze::printMaze() const 
{
    for(int i = 0; i < MAZE_SIZE; i++){
        for(int j = 0; j < MAZE_SIZE; j++){
			Room r = _rooms[i][j];
			_rooms[i][j].print(i*5,j*3);
			wcout << endl;
        }        
    }    
}

int Maze::getGoldRoom(const int i) const
{
	if (i < 0 || i > _tresCount-1) throw "Invalid treasure number";
	return _tresures[i];
}

Room Maze::getRoom(int const x, int const y) const
{
	if (!inBounds(x,y)) throw "Out of bounds";
	return this->_rooms[x][y];
}

// Sets up the top left room as the starting room with external doors where players will start the maze
void Maze::setStartPoint()
{
	_rooms[0][0].setDoors(1, 0, 0, 1);
	_rooms[0][0].setOuterRoom(1);
	// set outerrooms
	for (int i = 0; i < MAZE_SIZE - 1; i++) {
		_rooms[i][0].setOuterRoom(1);
		_rooms[0][i].setOuterRoom(1);
		_rooms[i][MAZE_SIZE - 1].setOuterRoom(1);
		_rooms[MAZE_SIZE - 1][i].setOuterRoom(1);
	}
}

void Maze::plantGold(const int count)
{
	setTresCount(count);
	srand((int)time(0)); // Initialize random seed using current time

	// Calculations
	int i = 0;
	int goldPos;
	bool dup = 0;	// flag to check if duplicate random numbers has been generated
	
	// Randomize treasure position while making sure no tresures are in the same room
	while (i < count) {
		goldPos = rand() % (2 * MAZE_SIZE - 2);
		for (int j = 0; j < count; j++) {
			if (goldPos == _tresures[j]) {
				dup = 1; 
				break;
			}
		}
		if (dup == 0) {
			_tresures[i] = goldPos;
			i++;
		}
		dup = 0;
	}
	int goldAmount;

	// insert gold to randomized rooms
	for (int i = 0; i < count; i++) {
		goldAmount = (rand() % 3 + 1) * 15;	// randomize prizes 15$, 30$, 45$
		if (_tresures[i] < MAZE_SIZE) // the gold is on the bottom row
		{
			_rooms[_tresures[i]][MAZE_SIZE - 1].setTreasure(goldAmount);	
			_rooms[_tresures[i]][MAZE_SIZE - 1].setDoors(0, 0, 1, 0);
			_rooms[_tresures[i]][MAZE_SIZE - 1].setOuterRoom(1);
		}
		else // the gold is on the right most column
		{
			int row = (2 * MAZE_SIZE - 2) - _tresures[i];
			_rooms[MAZE_SIZE - 1][row].setTreasure(goldAmount);
			_rooms[MAZE_SIZE - 1][row].setDoors(0, 1, 0, 0);
			_rooms[MAZE_SIZE - 1][row].setOuterRoom(1);
		}
	}
}

// once the treasure has been assigned to the rooms, this method builds paths from each treasure to the starting position of the maze
void Maze::buildGoldPaths(const int count)
{
	for (int i = 0; i < count; i++) // this needs to be a for loop later
	{
		int pathDir;
		int goldX, goldY;
		bool pathComplete = false;
		if (_tresures[i] < MAZE_SIZE)
		{
			goldX = _tresures[i];
			goldY = MAZE_SIZE - 1;
		}
		else {
			goldX = MAZE_SIZE - 1;
			goldY = (2 * MAZE_SIZE - 2) - _tresures[i];
		}
		srand((int)time(0)); // Initialize random seed using current time
		while (!pathComplete) {
			pathDir = rand() % (100); 
			// move up
			if (pathDir >= 0 && pathDir <=39) {
				if (inBounds(goldX, goldY - 1)) {
					_rooms[goldX][goldY].toggleDoors(0);
					goldY--;
					_rooms[goldX][goldY].toggleDoors(2);
				}
			}
			// move right
			if (pathDir >= 90 && pathDir <= 99) {
				if (inBounds(goldX + 1, goldY)) {
					_rooms[goldX][goldY].toggleDoors(1);
					goldX++;
					_rooms[goldX][goldY].toggleDoors(3);
				}
			}
			// move down
			if (pathDir >= 80 && pathDir <= 89) {
				if (inBounds(goldX, goldY + 1)) {
					_rooms[goldX][goldY].toggleDoors(2);
					goldY++;
					_rooms[goldX][goldY].toggleDoors(0);
				}
			}
			// move left
			if (pathDir >= 40 && pathDir <= 79) { 
				if (inBounds(goldX - 1, goldY)) {
					_rooms[goldX][goldY].toggleDoors(3);
					goldX--;
					_rooms[goldX][goldY].toggleDoors(1);
				}
			}
			if (goldX == 0 && goldY == 0)
				pathComplete = true;
		}
	}
}

// randomize doors in each room and fix single doors between rooms using fixSingleDoors(i,j);
void Maze::randomizeRooms()
{
	int num = 0;
	bool toggleDoors[4] = { 0,0,0,0 };
	for (int i = 0; i < MAZE_SIZE; i++)	// randomize EACH room in the maze 
	{
		for (int j = 0; j < MAZE_SIZE; j++) {
			for (int k = 0; k < 4; k++)	// make an array of which doors to toggle
			{
				num = rand() % (4); // 4 is the seed for the amount of doors, the higher the number the less likely a door will be randomized 
				if (num == 1)
					toggleDoors[k] = num;
			}
			_rooms[i][j].toggleDoors(toggleDoors);
			fixSingleDoors(i,j);
			toggleDoors[0] = 0;
			toggleDoors[1] = 0;
			toggleDoors[2] = 0;
			toggleDoors[3] = 0;
		}
	}
}

// whenever there are two adjesent rooms next to eachother, this method makes sure they both have doors pointing at eachother rather than only 1 door
void Maze::fixSingleDoors(const int x, const int y)
{
	for (int i = 0; i < 4; i++) {
		int updateX = 0, updateY = 0;
		if (i == 0) {
			updateY = -1;
		}
		else if (i == 2) {
			updateY = 1;
		}
		else if (i == 1) {
			updateX = 1;
		}
		else if (i == 3) {
			updateX = -1;
		}
		bool currRoom = _rooms[x][y].getDoors(i);
		if (currRoom && inBounds(x + updateX, y + updateY))
		{
			_rooms[x+updateX][y+updateY].toggleDoors((i+2)%4);
		}
	}
}

extern bool inBounds(const int x, const int y)
{
	if (x > MAZE_SIZE - 1 || x < 0 || y<0 || y > MAZE_SIZE - 1)
		return false;
	else return true;
}
