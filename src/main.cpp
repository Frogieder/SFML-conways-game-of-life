#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "./config/confProcess.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        shape.move(circle_offset_per_frame, circle_offset_per_frame);
        if (shape.getPosition().y > 600)
        {
            shape.setPosition(0, 0);
        }

        window.clear();
        window.draw(shape);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
    return 0;
}