#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();

private:
	GameManager* _gameManager;

	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;
	sf::RectangleShape _progressBar;
	sf::RectangleShape _progressBarFill;

	std::vector<sf::CircleShape> _lives;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};
