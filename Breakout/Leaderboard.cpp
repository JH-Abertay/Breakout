#include "Leaderboard.h"
#include <iostream>

Leaderboard::Leaderboard(sf::RenderWindow* window) : _leaderboardText(_font)
{
	_window = window;

	_leaderboardText.setCharacterSize(32);
	_leaderboardText.setPosition({400, 10});
	_leaderboardText.setFillColor(sf::Color::Cyan);
	if (!_font.openFromFile("font/montS.ttf")) {
		std::cout << "ERROR: Failed to load font in Leaderboard" << "\n";
	}
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::render()
{
	_window->draw(_leaderboardText);
}
