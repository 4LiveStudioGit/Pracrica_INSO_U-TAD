#pragma once
#include <windows.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
class Game 
{
private:
    Player player;
    Enemy enemies[6];
    Bullet bullet;
    bool shoot;
    bool leftBullet;
    int spawntime; 
    char map[31];
    int enemydeath = 0;
    int spawner = 0;
    

public:
    Game() : player(16), shoot(false), leftBullet(false), bullet(100)
    {
        for (int i = 0; i < 6; i++)
        {
             enemies[i].setPosition(199);
        }
    }

    void run() 
    {
        spawntime = 0;
        while (true) 
        {
            
            update();
            render();
            Sleep(200);
            
            //Comprobamos si algun enemigo alcanza al player para establecer el fin de la partida
            for (int i = 0; i < 6; i++)
            {
                if (enemies[i].ingame)
                {
                    if (enemies[i].getPosition() == player.getPosition())
                    {
                        gameOver();
                        break;
                    }
                }
            }

        }
    }

    void update()
    {
        
        if (spawntime == 0)
        {
            for (int i = 0; i < 6; i++)
            {
                if (enemies[i].ingame == false)
                {
                    enemies[i].ingame = true;
                    enemies[i].spawn();
                    if (enemydeath == 5)
                    {
                        spawner++;
                    }
                    if (spawner < 3)
                    {
                        spawntime = 5 - spawner;
                    }
                    else 
                    {
                        spawntime = 1;
                    }
                    break;
                }
            }
        }
        spawntime--;
        // Movimiento del jugador a la izquierda al pulsar IZQ
        if (GetAsyncKeyState(0x25))
        {
            player.moveLeft();
            
        }

        // Movimiento del jugador a la derecha al pulsar DCHA 
        if (GetAsyncKeyState(0X27))
        {
            player.moveRight();
           
        }

        

        //Si no existe disparo se permite disparar
        if (!shoot)
        {

            //Si presiona la tecla A se dispara a la izquierda
            if (GetAsyncKeyState(0x41))
            {
                bullet.setPosition(player.getPosition() - 1);
                shoot = true;
                leftBullet = true;
            }
            //Si presiona la tecla D se dispara a la derecha
            if (GetAsyncKeyState(0x44))
            {
                bullet.setPosition(player.getPosition() + 1);
                shoot = true;
                leftBullet = false;
            }
        }

        if (shoot)
        {
            //Comprobamos si la bala debe moverse a la izquierda o a la derecha
            if (leftBullet)
            {
                bullet.moveLeft();
            }
            else
            {
                bullet.moveRight();
            }
            //Comprobamos si la bala esta dentro de los limites del campo
            if ((bullet.getPosition() >= 31) || (bullet.getPosition() <= -1))
            {
                shoot = false;
            }

            for (int i = 0; i < 6; i++)
            {
                //Si el enemigo viene por la derecha
                if (!enemies[i].direction)
                {
                    //Comprobamos si la bala colisiona con algun enemigo por la derecha
                    if (bullet.getPosition() >= enemies[i].getPosition())
                    {
                        enemies[i].setPosition(200);
                        enemies[i].ingame = false;
                        bullet.setPosition(100);
                        shoot = false;
                        enemydeath++;
                    }
                }
                //Si el enemigo viene por la izquierda
                else
                {
                    if (bullet.getPosition() <= enemies[i].getPosition())
                    {
                        enemies[i].setPosition(200);
                        enemies[i].ingame = false;
                        bullet.setPosition(100);
                        shoot = false;
                        enemydeath++;

                    }
                }

            }
        }

        // Movemos a los enemigos
        for (int i = 0; i < 6; i++)
        {
            if (enemies[i].ingame)
            {
                enemies[i].move();
            }
        }
        Sleep(200);
    }

    //Pintamos la nueva situación de la partida con cada una de las posiciones tanto del jugador
    //como de la bala y de los enemigos.
    void render() 
    {
        system("cls");
        for (int i = 0; i < 31; ++i)
        {
            map[i] = '_';
        }
        map[player.getPosition()] = 'A';
        map[bullet.getPosition()] = '-';
        for (int i = 0; i < 6; i++)
        {
            map[enemies[i].getPosition()] = 'O';
        }
          
        for (int i = 0; i < 31; ++i)
        {
           printf("%c",map[i]);
        }
    }

    void gameOver() 
    {
        system("CLS");
        printf("\n ---------------- GAME OVER ---------------------");
        Sleep(1000);
    }



};