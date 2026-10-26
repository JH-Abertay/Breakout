#include "LocalLeaderboard.h"
#include <algorithm>

LocalLeaderboard::LocalLeaderboard(sf::RenderWindow* window) : Leaderboard(window)
{
}

void LocalLeaderboard::retrieveScore()
{
	_scores.push_back(std::pair<std::string, float>("I don't know", 100));
	_scores.push_back(std::pair<std::string, float>("what I was", 300));
	_scores.push_back(std::pair<std::string, float>("thinking,", 500));
	_scores.push_back(std::pair<std::string, float>("leaving my", 200));
	_scores.push_back(std::pair<std::string, float>("child behind", 650));
	_scores.push_back(std::pair<std::string, float>("Now I suffer", 120));
	_scores.push_back(std::pair<std::string, float>("the curse, and", 370));
	_scores.push_back(std::pair<std::string, float>("now I", 280));
	_scores.push_back(std::pair<std::string, float>("am blind", 720));

	std::sort(_scores.begin(), _scores.end(), [](std::pair<std::string, float> a, std::pair<std::string, float> b) {
		return a.second > b.second;
		});
}

void LocalLeaderboard::sendScore(std::string name, float score)
{
	_scores.push_back(std::pair(name, score));
	std::sort(_scores.begin(), _scores.end(), [](std::pair<std::string, float> a, std::pair<std::string, float> b) {
		return a.second > b.second;
		});

	std::string leaderboardString = "";

	for (size_t i = 0; i < _scores.size(); i++)
	{
		leaderboardString += _scores[i].first + ": " + std::to_string((int)_scores[i].second) + "\n";
	}

	_leaderboardText.setString(leaderboardString);
}
