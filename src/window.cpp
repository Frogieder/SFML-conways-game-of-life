#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "./game.hpp"
#include "./config/confProcess.hpp"

int RunGame()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Life");

    /*  Cells vertex array

            0--3--4--7
            |  |  |  |
            1--2--5--6
            8--b--c--f
            |  |  |  |
            9--a--d--e

        (1 = 8; 2 = b; 5 = c; 6 = f)
    */
    sf::Vertex cells_vertices[cell_count * 2 + 2 * y_size];
    for (int row = 0; row < y_size; row++)
    {
        for (int column = 0; column <= x_size; column++)
        {
            int position = row * (x_size + 1) * 2 + (column * 2);
            float x = column * cellsize;
            float y = row * cellsize;
            if ((column % 2) == 0)
            {
                cells_vertices[position] = sf::Vertex(sf::Vector2f(x, y));
                cells_vertices[position + 1] = sf::Vertex(sf::Vector2f(x, y + cellsize));
            }
            else
            {
                cells_vertices[position] = sf::Vertex(sf::Vector2f(x, y + cellsize));
                cells_vertices[position + 1] = sf::Vertex(sf::Vector2f(x, y));
            }
        }
    }

    // FPS counter
    sf::Text FPS_text;
    FPS_text.setCharacterSize(24);
    FPS_text.setFillColor(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("../../fonts/Roboto-Bold.ttf");
    FPS_text.setFont(font);
    sf::Clock FPS_timer;

    // game controller and game grid creation
    gameFunctions gameController(x_size, y_size);
    bool *game_grid;
    game_grid = gameController.generateGrid(gridGenerators::random, non_density);

    // clock to measure time between updates
    sf::Clock updateTimer;

    // Clock to measure time of each frame.
    // Naming is inspired by Unity
    sf::Clock delta_time_clk;
    sf::Time delta_time;

    /*###########################\
    #          Game loop         #
    \###########################*/
    while (window.isOpen())
    {
        /*----------------------------\
        |        Event capture        |
        \----------------------------*/

        //capture all events each frame
        sf::Event event;
        while (window.pollEvent(event))
        {
            // window closed event - close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*----------------------------\
        |         State update        |
        \----------------------------*/

        //unreadable mess that reads time from clock, resets it,
        //uses the time to calculate FPS and sets text to FPS rounded to whole numbers
        FPS_text.setString(std::to_string(static_cast<int>(1/FPS_timer.restart().asSeconds())));

        if (updateTimer.getElapsedTime() >= sf::seconds(speed))
        {
            updateTimer.restart();
            game_grid = gameController.updateGrid();
        }

        /*----------------------------\
        |            Drawing          |
        \----------------------------*/
        window.clear();

        for (int y = 0; y < y_size; y++)
        {
            for (int x = 0; x < x_size; x++)
            {
                if (game_grid[y * y_size + x])
                    window.draw(cells_vertices + y * (y_size * 2 + 2) + x * 2, 4, sf::Quads);
            }
        }

        window.draw(FPS_text);

        window.display();

        /*----------------------------\
        |           Sleeping          |
        \----------------------------*/
        delta_time = delta_time_clk.getElapsedTime();
        if (delta_time < sf::microseconds(frametime))
        {
            sf::sleep(sf::microseconds(frametime) - delta_time);
        }
        delta_time_clk.restart();
    }
    return 0;
}