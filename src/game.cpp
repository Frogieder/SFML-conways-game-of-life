#include <iostream>
#include "game.hpp"
#include <time.h>
#include <stdlib.h>

gameFunctions::gameFunctions(int _x, int _y)
{
    game_field_a = new bool[_x * _y];
    game_field_b = new bool[_x * _y];
    x_size = _x;
    y_size = _y;
}

gameFunctions::~gameFunctions()
{
    delete game_field_a;
    delete game_field_b;
}

bool *gameFunctions::generateGrid(gridGenerators generator, int non_density)
{
    if (generator == gridGenerators::clean)
    {
        for (int i = 0; i < x_size * y_size; i++)
        {
            game_field_a[i] = 0;
            game_field_b[i] = 0;
        }
    }
    else if (generator == gridGenerators::random)
    {
        srand(time(NULL));
        for (int i = 0; i < x_size * y_size; i++)
        {
            if (rand() % non_density == 0)
            {
                game_field_a[i] = 1;
                game_field_b[i] = 1;
            }
            else 
            {
                game_field_a[i] = 0;
                game_field_b[i] = 0;
            }
        }
    }
    return this->game_field_a;
}

int gameFunctions::checkNeighbours(int x, int y, bool *game_field)
{
    int neighbours = 0;
    for (int delta_y = -1; delta_y <= 1; delta_y++)
    {
        for (int delta_x = -1; delta_x <= 1; delta_x++)
        {
            if (delta_y + y >= 0 && delta_x + x >= 0)
            {
                if (delta_y + y < y_size && delta_x + x < x_size)
                {
                    if (game_field[(y + delta_y) * y_size + x + delta_x])
                    {
                        if (delta_x != 0 || delta_y !=0)
                            neighbours++;
                    }
                }
            }
        }
    }
    return neighbours;
}

//checks the conditions according to the life
void gameFunctions::internalUpdateGrid(bool *source_game_field, bool *target_game_field)
{
    for (int y = 0; y < y_size; y++)
    {
        for (int x = 0; x < x_size; x++)
        {
            int neigbours = gameFunctions::checkNeighbours(x, y, source_game_field);
            if (source_game_field[x + y_size * y])
            {
                if (neigbours < 2 || neigbours > 3)
                {
                    target_game_field[x + y_size * y] = false;
                }
                else
                {
                    target_game_field[x + y_size * y] = true;
                }
            }
            else
            {
                if (neigbours == 3)
                {
                    target_game_field[x + y_size * y] = true;
                }
                else
                {
                    target_game_field[x + y_size * y] = false;
                }
            }
        }
    }
    return;
}

bool *gameFunctions::updateGrid()
{
    // update older grid and make it newer
    if (active_a)
    {
        this->internalUpdateGrid(game_field_a, game_field_b);
        active_a = !active_a;
        return game_field_b;
    }
    else
    {
        this->internalUpdateGrid(game_field_b, game_field_a);
        active_a = !active_a;
        return game_field_a;
    }
}
