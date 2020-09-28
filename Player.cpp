#include "Player.h"

Player::Player() 
{
}

void Player::setAI()
{
    this->_ai = true;
}


bool Player::move(const int dir, const Maze& curMaze)
{
    Room curRoom = curMaze.getRoom(this->_x, this->_y); // get current room at player's location
    const bool *openDoors = curRoom.getDoors(); // get current room's open doors

    if(openDoors[dir] && dir >= 0 && dir <= 3) // move if a door is open
    {
        this->_score--;
        printScore(_ai);
        switch(dir){
            case 0:
                this->_y--;
                break;
            case 1:
                this->_x++;
                break;
            case 2:
                this->_y++;
                break;
            case 3:
                this->_x--;
                break;
        }
    }
    return openDoors[dir];
}



bool Player::inMaze() const
{
    if (_x < 0 || _x > MAZE_SIZE - 1 || _y < 0 || _y > MAZE_SIZE - 1)
        return false;

    return true;
}

bool Player::isOnGold(const Maze& curMaze){
   const Room curRoom = curMaze.getRoom(this->_x, this->_y);
   if(curRoom.getTreasure() > 0)
            return true;

   return false;
}

void Player::resetPlayer()
{
    _x = 0;
    _y = 0;
}

void Player::printScore(const bool ai)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, CYAN);
    if (ai == false) {
        setCursorCoord(TEXT_AXIS, 17);
        wcout << "Player 1 Score: " << _score << "  ";
    }
    else
    {
        setCursorCoord(TEXT_AXIS, 18);
        wcout << "Player 2 Score: " << _score << "  ";
    }
}

bool Player::sameRoom(const Player& other)
{
    if (this->getX() == other.getX() && this->getY() == other.getY())
        return true;
    else
        return false;
}

void Player::printPlayer()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, PLAYER_COLOR);
    if (this->_ai == 0) {
        setCursorCoord((_x * 5) + 2, (_y * 3) + 1);
        wcout << L"☺";
    }
    else
    {
        setCursorCoord((_x * 5) + 1, (_y * 3) + 1);
        wcout << L"¤";
    }
}

void Player::erasePlayer(const int x, const int y)
{
    if (this->_ai == 0)
        setCursorCoord((x * 5) + 2, (y * 3) + 1);
    else
        setCursorCoord((x * 5) + 1, (y * 3) + 1);
    wcout << L" ";
}

/*
void Player::setCursorCoord(int column, int row)
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
*/
         