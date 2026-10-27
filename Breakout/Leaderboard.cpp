#include "Leaderboard.h"
#include <iostream>

Leaderboard::Leaderboard(sf::RenderWindow* window)
{
	_window = window;

	_leaderboardText.setCharacterSize(32);
	_leaderboardText.setPosition(400, 10);
	_leaderboardText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_leaderboardText.setFont(_font);
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::render()
{
	_window->draw(_leaderboardText);
}
