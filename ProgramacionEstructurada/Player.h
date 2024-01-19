#pragma once
class Player
{
public:
    Player(int startPos) : position(startPos) {}

    void moveLeft() 
    {
        position--;
    }

    void moveRight() 
    {
        position++;
    }

    int getPosition() const 
    {
        return position;
    }

    void setPosition(int pos) 
    {
        position = pos;
    }

private:
    int position;
};


