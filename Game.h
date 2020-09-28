#pragma once
#include "Room.h"
#include "Maze.h"
#include "Player.h"
#include <conio.h>
#include <math.h>

#define NUM_OF_ROUNDS 3
#define NUM_OF_PLAYERS 2

// Define arrow key codes
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

class Game
{
private:
    Maze _mazes[NUM_OF_ROUNDS];
    int _mainPlayerX = 0;
    int _mainPlayerY = 0;
    Player _players[NUM_OF_PLAYERS];
    bool _playerVSai = 1;
    int _roundNumber = 0;
public:
    Game();
    
    void start();
private:
    int playGame(const bool aiVSai, const bool testRun);
    void endGame(const int winner);
    void const printLogo() const;
    void const slowErase() const;

    int keyPressDetection() const;
    int keyPressDetectionAtStartUp() const;

    void eraseRoom(int x, int y) const;
    void playerOnGold(int x0, int y0, int round, int plyrNum);
    void playerOutside(int x0, int y0, int plyrNum);
    double getClosestTreasure(const int round);
    bool peakRoom(const int pressedKey, const int round, const bool testRun);
    bool playerMove(const int playerNumber, const int round, const int pressedKey, const int testRun, const bool aiVSai);
    int randomizeAiMove(const int round, const int plyrNum, bool firstMove) const;

    void initRound(const int round, const bool testRun);
    void roundReset(const int seconds) const;
    void printRoundInstruct() const;
};
