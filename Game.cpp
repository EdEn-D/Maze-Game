#include "Game.h"

Game::Game()
{
	for (int i = 0; i < NUM_OF_ROUNDS; i++)
    {
        Maze maze(MAX_TRESURES -i);
		_mazes[i] = maze;
    }
}

void Game::initRound(const int round, const bool testRun)
{        
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, YELLOW);
    setCursorCoord(TEXT_AXIS, 0);
    wcout << "Round " << round +1;
    setCursorCoord(TEXT_AXIS, 1);
    wcout << "-------";

    printRoundInstruct();

    if (testRun == 1)
            _mazes[round].printMaze(); // testing print

        _players[1].setAI(); // second player always AI
        _mazes[round].getRoom(0, 0).print(0,0);// Always print starting room
        _players[1].printScore(1);
        _players[0].printScore(0);
        _players[0].printPlayer();
        _players[1].printPlayer();  
}


bool Game::peakRoom(const int pressedKey, const int round, const bool testRun)
{
    //x and y are going to be the requested peak room
    int x = _players[0].getX();
    int y = _players[0].getY();
    switch (pressedKey) { // detect arrow keys
    case 10:
        y--;
        break;
    case 11:
        x++;
        break;
    case 12:
        y++;
        break;
    case 13:
        x--;
        break;
    }

    if (inBounds(x, y)) {
        // deduct points for using help
        _players[0].addScore(-1);
        _players[0].printScore(0);
        // show the room
        _mazes[round].getRoom(x, y).print(x * 5, y * 3);
        // print ai if he's in the peaked room
        if (x == _players[1].getX() && y == _players[1].getY())
            _players[1].printPlayer();

        setCursorCoord(TEXT_AXIS, 9);
        wcout << "Peaking room - ";
        system("pause");
        setCursorCoord(TEXT_AXIS, 9);
        wcout << "                                                  ";
        if (testRun == 0)
            eraseRoom(x * 5, y * 3);
        return true;
    }
    else 
        return false;
}

double Game::getClosestTreasure(const int round)
{
    _players[0].addScore(-1);
    _players[0].printScore(0);
    const int numOfTres = _mazes[round].getTresCount();
    double newDist = 0, curDist = 0; //DBL_MAX

    for (int i = 0; i < numOfTres; i++)
    {
        int roomPos = _mazes[round].getGoldRoom(i);
        int roomPosX, roomPosY;

        // Convert roomPos to X, Y coordinates, relative to [0, 0]
        if (roomPos < MAZE_SIZE) // if treasure is at the bottom, -1 in the x direction, we can safely assume it's coordinates are (x, MAZE_SIZE-1)
        {
            roomPosX = roomPos;
            roomPosY = MAZE_SIZE - 1;
        }
        else // otherwise we safely assume x is MAZE_SIZE-1 and calculate the the y coordinate
        {
            roomPosX = MAZE_SIZE - 1;
            roomPosY = (2 * MAZE_SIZE - 2) - roomPos;

        }

        // calculate air distance using Pythagorian's theorem equation
        newDist = sqrt(pow(_players[0].getX() - roomPosX, 2) + pow(_players[0].getY() - roomPosY, 2));

        if (newDist < curDist || !curDist) // check if new distance is the smallest and make sure that in first iteration curDist will be updated
            curDist = newDist; // insert new smallest distance
    }

    // return 1.5;
    return curDist;
}

void const Game::printLogo() const
{
    //wcout << L"" << endl;
    wcout << L"  ▄████▄   ▒█████   ██▒   █▓ ██▓▓█████▄           " << endl; Sleep(100);
    wcout << L" ▒██▀ ▀█  ▒██▒  ██▒▓██░   █▒▓██▒▒██▀ ██▌          " << endl; Sleep(100);
    wcout << L" ▒▓█    ▄ ▒██░  ██▒ ▓██  █▒░▒██▒░██   █▌          " << endl; Sleep(100);
    wcout << L" ▒▓▓▄ ▄██▒▒██   ██░  ▒██ █░░░██░░▓█   █           " << endl; Sleep(100);
    wcout << L" ▒ ▓███▀ ░░ ████▓▒░   ▒▀█░  ░██░░▒█████           " << endl; Sleep(100);
    wcout << L" ░ ░▒ ▒  ░░ ▒░▒░▒░    ░ ▐░  ░▓   ▒▒▓  ▒           " << endl; Sleep(100);
    wcout << L"   ░  ▒     ░ ▒ ▒░    ░ ░░   ▒ ░ ░ ▒  ▒           " << endl; Sleep(100);
    wcout << L" ░        ░ ░ ░ ▒       ░░   ▒ ░ ░ ░  ░           " << endl; Sleep(100);
    wcout << L" ░ ░          ░ ░        ░   ░     ░              " << endl; Sleep(100);
    wcout << L" ░                      ░        ░                " << endl; Sleep(100);
    wcout << L"              ███▄ ▄███▓ ▄▄▄      ▒███████▒▓█████ " << endl; Sleep(100);
    wcout << L"             ▓██▒▀█▀ ██▒▒████▄    ▒ ▒ ▒ ▄▀░▓█   ▀ " << endl; Sleep(100);
    wcout << L"             ▓██    ▓██░▒██  ▀█▄  ░ ▒ ▄▀▒░ ▒███   " << endl; Sleep(100);
    wcout << L"             ▒██    ▒██ ░██▄▄▄▄██   ▄▀▒   ░▒▓█  ▄ " << endl; Sleep(100);
    wcout << L"             ▒██▒   ░██▒ ▓█   ▓██▒▒███████▒░▒████▒" << endl; Sleep(100);
    wcout << L"             ░ ▒░   ░  ░ ▒▒   ▓▒█░░▒▒ ▓░▒░▒░░ ▒░ ░" << endl; Sleep(100);
    wcout << L"             ░  ░      ░  ▒   ▒▒ ░░░▒ ▒ ░ ▒ ░ ░  ░" << endl; Sleep(100);
    wcout << L"             ░      ░     ░   ▒   ░ ░ ░ ░ ░   ░   " << endl; Sleep(100);
    wcout << L"                    ░         ░  ░  ░ ░       ░  ░" << endl; Sleep(100);
    wcout << L"                                  ░               " << endl; Sleep(400);
}

void const Game::slowErase() const
{
    for (int i = 0; i < 30; i++) {
        wcout << L"                                                      " << endl;
        Sleep(120);
    }
}

// start game splash screen
void Game::start()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, RED);
    printLogo();
    wcout << "Welcome to the greatest Maze game ever created" << endl;
    wcout << L"──────────────> ESCAPE OR DIE <───────────────" << endl;
    SetConsoleTextAttribute(h, MAGENTA);
    wcout << L"\nChoose game mode: " << endl;
    //wcout << L" " << endl;
    wcout << L"1. Player vs. AI " << endl;
    wcout << L"2. AI vs. AI " << endl;
    int aiVSai = keyPressDetectionAtStartUp();
    wcout << L"\nPress T for Test Mode (See full maze - Recommended for beginners)" << endl;
    wcout << L"Press R for Real Challange Mode (For professional gamers ONLY!)" << endl;
    int key2 = keyPressDetectionAtStartUp();
    system("CLS");
    if (key2 == 2) // R
        key2 = 0;
    else if (key2 == 3) // T
        key2 = 1;
    int winner = playGame(aiVSai, key2);
    endGame(winner);
}

// Splash screen for when the game ends
void Game::endGame(const int winner)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, RED);
    system("CLS");
    printLogo();
    if (winner == 0) { // tie
        setCursorCoord(0, 5);
        SetConsoleTextAttribute(h, WHITE);
        wcout << "The game is a tie! Both players are ";
        SetConsoleTextAttribute(h, RED);
        wcout << "DEAD!";
    }
    else if (winner == 1 || winner == 2) { // p1 win or p2 win
        int loser = 0;
        if (winner == 1)
            loser = 2;
        else if (winner == 2)
            loser = 1;
        setCursorCoord(12, 22);
        SetConsoleTextAttribute(h, GREEN);
        wcout << "Player " << winner << " in the Winner!" << endl;
        SetConsoleTextAttribute(h, YELLOW);
        setCursorCoord(12, 23);
        wcout << "Player " << loser << " is ";
        SetConsoleTextAttribute(h, RED);
        wcout << "DEAD!";
        setCursorCoord(12, 25);
        SetConsoleTextAttribute(h, MAGENTA);
        wcout << "Thank you for playing.";
        setCursorCoord(12, 26);
        wcout << "Press R to restart or Press T to end game";
        int key = keyPressDetectionAtStartUp();
        if (key == 2) { // R
            system("CLS");
            // delete new game and construct new one
            this->~Game();
            Game newGame;
            newGame.start();
        }
        else if (key == 3) // T
        {
            setCursorCoord(0, 0);
            slowErase();
        }
    }
}

bool Game::playerMove(const int plyrNum, const int round, const int pressedKey, const int testRun, const bool aiVSai)
{
    bool playerMoved = false;
    if (_players[plyrNum].inMaze()) {
        // Player's position pre move
        int oldx0 = _players[plyrNum].getX();
        int oldy0 = _players[plyrNum].getY();
        // player move - returns false if player stayed in the same position
        playerMoved = _players[plyrNum].move(pressedKey, _mazes[round]);
        // player position post move
        int x0 = _players[plyrNum].getX();
        int y0 = _players[plyrNum].getY();
        
        if (!playerMoved)
            return false;

        if (_players[plyrNum].inMaze()) {
            // erase old player character
            _players[plyrNum].erasePlayer(oldx0, oldy0);

            // print the room that the player moved into
            if (plyrNum == 0 || aiVSai == 1)
            _mazes[round].getRoom(x0, y0).print(x0 * 5, y0 * 3);

            // check if player is on gold
            if (_mazes[round].getRoom(x0, y0).getTreasure() > 0)
            { // on gold
                playerOnGold(x0, y0, round, plyrNum);
                return true;
                //break;
            }
            else
            { // not on gold
                if (plyrNum == 0 || _players[0].sameRoom(_players[1]) || testRun == 1 || aiVSai == 1)
                _players[plyrNum].printPlayer();  // print the player in the new room he moved into
                // erase old room
                if (testRun == 0 && !(oldx0 == x0 && oldy0 == y0) && !(_players[0].getX() == oldx0 && _players[0].getY() == oldy0))
                    eraseRoom(5 * oldx0, 3 * oldy0);
            }
        }
        // player left the maze without gold
        else if (!(_players[plyrNum].inMaze()))
        {
            _players[plyrNum].erasePlayer(oldx0, oldy0);
            if (testRun == 0 && !(oldx0 == x0 && oldy0 == y0) && !(_players[0].getX() == oldx0 && _players[0].getY() == oldy0))
                eraseRoom(5 * oldx0, 3 * oldy0);
            playerOutside(x0, y0, plyrNum);
        }
    }
    return true;
}

int Game::playGame(const bool aiVSai, const bool testRun)
{
    // I used this debug variable to enable some "debugging mode" features throughout this method while building it
    // I decided to keep it in the final code along with the debugging code just for show and to debug in the future if i ever revisit this project
    bool debug = 0;
    bool firstMove = 1;
    bool playerMoved = false;

    _players[0].resetPlayer();
    _players[0].setScore(0);
    _players[1].resetPlayer();
    _players[1].setScore(0);

	for (int round = 0; round < NUM_OF_ROUNDS; round++) {

        initRound(round, testRun);
        firstMove = 1;

        while ( _players[0].inMaze() || _players[1].inMaze() ) {
            if (debug) {
                setCursorCoord(90, 25);
                wcout << "Player 0 x, y:" << _players[0].getX() << "  " << _players[0].getY();
                setCursorCoord(90, 26);
                wcout << "Player 1 x, y:" << _players[1].getX() << "  " << _players[1].getY();
            }

            int pressedKey = 0;
            if (_players[0].inMaze())
                if (aiVSai == 0)
                    pressedKey = keyPressDetection();
                else if (aiVSai == 1)
                    pressedKey = randomizeAiMove(round, 0, firstMove);

            // player movement
            if (pressedKey >= 0 && pressedKey <= 3) {
                
                playerMoved = playerMove(0, round, pressedKey, testRun, aiVSai);
                if (!playerMoved)
                    continue;   // reset while loop to get keyboard key again because player ran into a wall (didn't move)
                // check if player reached gold
                if (_players[0].inMaze() && _mazes[round].getRoom(_players[0].getX(), _players[0].getY()).getTreasure() > 0)
                {
                    if (debug) {
                        setCursorCoord(TEXT_AXIS, 2);
                        wcout << "human reached gold";
                    }
                    roundReset(3);
                    break;
                }
            }

            // room peak
            if (pressedKey >= 10 && pressedKey <= 13) {
                bool roomPeaked = 0;
                roomPeaked = peakRoom(pressedKey, round, testRun);
           
                if (!roomPeaked)
                   continue;
            }

            // treasure distance
            if (pressedKey == 5) {
                double distance = getClosestTreasure(round);
                setCursorCoord(TEXT_AXIS+26, 10);
                wcout << "               ";
                setCursorCoord(TEXT_AXIS, 10);
                wcout << "Distance to closest treasure: " << distance;                
            }

            if (aiVSai == 1)
                Sleep(100);
             
            ///////////////////////////////////// AI MOVE //////////////////////////////////////////////
            // if player didnt reach gold, ai gets a turn
            if (_players[1].inMaze()) {

                int randKey = randomizeAiMove(round, 1, firstMove);
                firstMove = 0;

                playerMove(1, round, randKey, testRun, aiVSai);
            }
            // check if ai got gold
            if (_players[1].inMaze() && _mazes[round].getRoom(_players[1].getX(), _players[1].getY()).getTreasure() > 0)
            {
                if (debug) {
                    setCursorCoord(TEXT_AXIS, 2);
                    wcout << "ai reached gold";
                }
               roundReset(3);
               break;
            }
                
            if (debug) {
               setCursorCoord(90, 25);
               wcout << "Player 0 x, y:" << _players[0].getX() << "  " << _players[0].getY();
               setCursorCoord(90, 26);
               wcout << "Player 1 x, y:" << _players[1].getX() << "  " << _players[1].getY();
           }

            if (debug) {
               setCursorCoord(TEXT_AXIS, 20);
               wcout << pressedKey << "  ";
               setCursorCoord(TEXT_AXIS, 21);
           }
            ///////////////////////////////////// AI MOVE //////////////////////////////////////////////

        }
        // check if both players left the maze 
        if (!(_players[0].inMaze()) && !(_players[1].inMaze())) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, YELLOW);
            setCursorCoord(TEXT_AXIS, 14);
            wcout << "Both playes left";
            roundReset(3);
        }

        _players[0].resetPlayer();
        _players[1].resetPlayer();

        if (debug) {
            // debugging shit
            setCursorCoord(TEXT_AXIS, 25);
            wcout << "Players reset";
            Sleep(1000);
            setCursorCoord(TEXT_AXIS, 25);
            wcout << "             ";
        }
	}
    if (_players[0].getScore() > _players[1].getScore())
        return 1;
    else if (_players[0].getScore() < _players[1].getScore())
        return 2;
    else if (_players[0].getScore() == _players[1].getScore())
        return 0;
        
    return 1;
}

int Game::randomizeAiMove(const int round, const int plyrNum, bool firstMove) const
{
    // ai movement
    Room curRoom = _mazes[round].getRoom(_players[plyrNum].getX(), _players[plyrNum].getY()); // Get current room at player's location
    const bool* openDoors = curRoom.getDoors(); // Get current room's open doors
    
    int randKey = 1;

    // random bias towards down and right
    do {
    // make sure ai doesn't leave maze on first turn
        if (firstMove)
            randKey = (rand() % 2) + 1;
        else {
            randKey = (rand() % 6);
            if (randKey == 1) // 0 & 3 have only 1 chance
                randKey = 3;
            else if (randKey >= 2 && randKey < 4)
                randKey = 1;
            else if (randKey >= 4 && randKey < 6)
                randKey = 2;
        }

    } while (!openDoors[randKey]);

    return randKey;

}


int Game::keyPressDetection() const
{
    int returnValue = -1;

    // keep getting key presses until we get a valid key
    do{
        int key = _getch(); // get key press
            //return 2;
            switch(key){
                // arrow keys //
                case 224: // workaround for arrow keys (returns 224 first and then the arrow code)
                    switch(_getch()){ // detect arrow keys
                        case UP:
                            returnValue = 0;
                            break; 
                        case RIGHT:
                            returnValue = 1;
                            break;
                        case DOWN:
                            returnValue = 2;
                            break;
                        case LEFT:
                            returnValue = 3;
                            break;
                        default:
                            break;
                    }
                    break;

            // miscellaneous keys //
                case 'Q':
                case 'q':
                    returnValue = 4;
                    break;
                case 'E':
                case 'e':
                    returnValue = 5;
                    break;
                case 'W':
                case 'w':
                    returnValue = 10;
                    break;
                case 'D':
                case 'd':
                    returnValue = 11;
                    break;
                case 'S':
                case 's':
                    returnValue = 12;
                    break;
                case 'A':
                case 'a':
                    returnValue = 13;
                    break;
                case '1':
                    returnValue = 21;
                    break;
                case '2':
                    returnValue = 22;
                    break;
                case 'R':
                case 'r':
                    returnValue = 23;
                    break;
                case 'T':
                case 't':
                    returnValue = 24;
                    break;
            }
    }while(returnValue == -1); // did we get a valid key?

    return returnValue; // return key press
}

int Game::keyPressDetectionAtStartUp() const
{
    int returnValue = -1;

    // keep getting key presses until we get a valid key
    do {
        int key = _getch(); // get key press
        switch (key) {
        case '1':
            returnValue = 0;
            break;
        case '2':
            returnValue = 1;
            break;
        case 'R':
        case 'r':
            returnValue = 2;
            break;
        case 'T':
        case 't':
            returnValue = 3;
            break;
        }
    } while (returnValue == -1); // did we get a valid key?

    return returnValue; // return key press
}

void Game::eraseRoom(int x, int y) const
{
    setCursorCoord(x, y);
    wcout << "     ";
    setCursorCoord(x, y+1);
    wcout << "     ";
    setCursorCoord(x, y+2);
    wcout << "     ";
}

// print messages for when each player gets the gold
void Game::playerOnGold(int x0, int y0, int round, int plyrNum)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    _mazes[round].printMaze();
    setCursorCoord(TEXT_AXIS, 12 + plyrNum);
    _players[plyrNum].addScore(_mazes[round].getRoom(x0, y0).getTreasure());
    SetConsoleTextAttribute(h, GREEN);

    wcout << "Player "<< plyrNum + 1<< " got the gold! Player " << plyrNum + 1 << " Score: " << _players[plyrNum].getScore();

    // print the other player so he is visible when we printMaze after the round is over
    if (plyrNum == 0) {
        if (_players[1].inMaze())
            _players[1].printPlayer();
    }
    else
        if (_players[0].inMaze())
            _players[0].printPlayer();
}

// print messages for when each player moves outside the maze
void Game::playerOutside(int x0, int y0, int plyrNum)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, RED);
    if (plyrNum == 0) {
        setCursorCoord(TEXT_AXIS, 12);
        wcout << "Player 1 left the maze... Round over for you";
    }
    else if (plyrNum) {
        setCursorCoord(TEXT_AXIS, 13);
        wcout << "Player 2 left the maze... Round over for him";
    }
}

// desplay round over messages, and clear screen after countdown
void Game::roundReset(const int seconds) const
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, RED);
    setCursorCoord(TEXT_AXIS, 28);
    wcout << "Round Over. "; 
    system("pause");
    
    setCursorCoord(TEXT_AXIS, 28);
    wcout << "Moving on in  ...                           ";
    // countdown
    for (int i = seconds; i > 0; i--) 
    {
    setCursorCoord(TEXT_AXIS + 13 , 28);
    wcout << i;
    setCursorCoord(TEXT_AXIS + 18, 28);
    Sleep(1000);
    }

    system("CLS");
}

void Game::printRoundInstruct() const
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, WHITE);

    setCursorCoord(TEXT_AXIS, 4);
    wcout << L"Use arrow keys to move your player ☺";
    setCursorCoord(TEXT_AXIS, 6);
    wcout << L"Press Q: To stay in place";
    setCursorCoord(TEXT_AXIS, 7);
    wcout << L"Press E: To get distance to closest treasure ";
    setCursorCoord(TEXT_AXIS, 8);
    wcout << L"Press W, A, S, or D: To see contents of a nearby room ";
}

