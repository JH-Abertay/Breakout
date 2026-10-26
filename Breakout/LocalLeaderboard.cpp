#include "LocalLeaderboard.h"


LocalLeaderboard::LocalLeaderboard(sf::RenderWindow* window) : Leaderboard(window)
{
}

void LocalLeaderboard::retrieveScore()
{

}

void LocalLeaderboard::sendScore(std::string name, float score)
{
	_scores.push_back(std::pair(name, score));

	std::string leaderboardString = "";

	for (size_t i = 0; i < _scores.size(); i++)
	{
		leaderboardString += _scores[i].first + ": " + std::to_string((int)_scores[i].second) + "\n";
	}

	_leaderboardText.setString(leaderboardString);

	// Todo: Serialize scores to a file
}
