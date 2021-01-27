#include "../src/game.hpp"
#include <iostream>

int main()
{
    int x = 3;
    int y = 3;
    int size = x * y;

    gameFunctions gameController(x, y);

    bool *game_grid = gameController.generateGrid(gridGenerators::clean);
    game_grid[2] = 1;
    game_grid[0] = 1;
    game_grid[1] = 1;
    game_grid[4] = 1;
    int neighbours = gameController.checkNeighbours(1, 1, game_grid);
    if (neighbours != 3)
    {
        std::cout << neighbours << std::endl;
        return 1;
    }

    return 0;
}