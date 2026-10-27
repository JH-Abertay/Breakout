#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Breakout");
    GameManager gameManager(&window);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else {
                gameManager.handleEvent(event.value());
            }
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);

        window.clear();
        gameManager.render();
        window.display();
    }

    return 0;
}
