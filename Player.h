#pragma once
#include "Maze.h"

#define PLAYER_COLOR 15

class Player
{
private:
	int _score = 0;
	int _x = 0;
	int _y = 0;
	bool _ai = false;
public:
	Player();
	void setAI();
	bool move(const int dir, const Maze& curMaze);
	bool inMaze() const;
	bool isOnGold(const Maze& curMaze);
	void resetPlayer();
	int getX() const { return _x; };
	int getY() const { return _y; };
	int getScore() const { return _score; }
	void setScore(const int score) { _score = score; }
	void addScore(const int gold) { _score = _score + gold; }
	void printScore(const bool ai);
	bool sameRoom(const Player& other);
	void printPlayer();
	void erasePlayer(const int x, const int y);


};

