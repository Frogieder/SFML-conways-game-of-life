#include "../src/game.hpp"
#include <iostream>

int main()
{
    int x = 5;
    int y = 4;
    int size = x * y;

    gameFunctions gameController(x, y);

    bool *game_grid = gameController.generateGrid(gridGenerators::random, 2);
    int true_cells = 0;

    for (int i = 0; i < size; i++)
    {
        if (game_grid[i])
            true_cells++;
    }
    int coverage = true_cells * 100 / size;
    std::cout << "coverage: " << coverage << "%\n";

    if (coverage == 0)
    {
        std::cout << "ERROR:\nNo cells got generated by random generator. Try running this test again";
        return 1;
    }

    game_grid = gameController.generateGrid(gridGenerators::clean);
    for (int i = 0; i < size; i++)
    {
        if (game_grid[i])
        {
            std::cout << "Clear generator gave non-0 value";
            return 1;
        }
    }
    return 0;
}