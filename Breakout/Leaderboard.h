#pragma once
#include <vector>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>

class Leaderboard
{
public:
	Leaderboard(sf::RenderWindow* window);
	~Leaderboard();

	void render();

	// Function used to retrieve scores and assign them to _scores variable.
	virtual void retrieveScore() = 0;
	// Function used to add to wherever _scores are stored.
	virtual void sendScore(std::string name, float score) = 0;
protected:
	// In memory accessor for player scores
	std::vector<std::pair<std::string, float>> _scores;
	// Shows leaderboard scores
	sf::Text _leaderboardText;

private:
	sf::Font _font;

	sf::RenderWindow* _window;
};
