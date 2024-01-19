#pragma once
#include <cstdlib>
class Enemy
{
    private:
        int position = 200;
       

    public:
        bool direction = 0;
        bool ingame = false;
        
        
        void move() 
        {
            if (direction)
            {
                position += rand() % 2 + 1;
            }
            else
            {
                position -= rand() % 2 + 1;
            }
        }

        int getPosition() const 
        {
            return position;
        }

        void setPosition(int pos)
        {
            position = pos;
        }

        void spawn()
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            direction = rand() % 2;

            if (direction == 0) 
            {
                position = 30;
            }
            else
            {
                position = 0;
            }
            ingame = true;
        }
    };



