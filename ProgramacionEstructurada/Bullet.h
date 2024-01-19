#pragma once
class Bullet {
public:
    Bullet(int startPos) : position(startPos) {}

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
