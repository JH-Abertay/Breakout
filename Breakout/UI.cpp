#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager)
	: _window(window), _gameManager(gameManager), _powerupText(_font), _progressBar({200, 50}), _progressBarFill({200, 50})
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition({(LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING});
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition({800, 10});
	_powerupText.setFillColor(sf::Color::Cyan);
	if (!_font.openFromFile("font/montS.ttf")) {
		std::cout << "ERROR: Failed to load font in Leaderboard" << "\n";
	}
	_powerupText.setFont(_font);

	_progressBar.setOutlineColor(sf::Color::White);
	_progressBar.setFillColor(sf::Color::Transparent);
	_progressBar.setPosition({750, 50});

	_progressBarFill.setFillColor(sf::Color::Green);
	_progressBarFill.setPosition({750, 50});
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");

		break;
	}

	if (_powerupText.getString() != "") {
		_progressBarFill.setSize({_progressBar.getSize().x * (powerup.second / _gameManager->getPowerupManager()->powerup_initial_time), _progressBarFill.getSize().y});
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);
	if (_powerupText.getString() != "") {
		_window->draw(_progressBar);
		_window->draw(_progressBarFill);
	}
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}
