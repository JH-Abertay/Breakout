#include "LocalLeaderboard.h"
#include <algorithm>
#include <fstream>

LocalLeaderboard::LocalLeaderboard(sf::RenderWindow* window) : Leaderboard(window)
{
}

LocalLeaderboard::~LocalLeaderboard()
{
}

void LocalLeaderboard::retrieveScore()
{
	std::string line;
	std::ifstream leaderboardFile(leaderboardFileName);

	_scores.clear();

	if (leaderboardFile.is_open()) {
		while (std::getline(leaderboardFile, line))
		{
			size_t eq_pos = line.find_last_of("=");

			_scores.push_back(std::pair<std::string, int>(line.substr(0, eq_pos), std::atoi(line.substr(eq_pos + 1, std::string::npos).c_str())));
		}
		leaderboardFile.close();
	}

	std::sort(_scores.begin(), _scores.end(), [](std::pair<std::string, float> a, std::pair<std::string, float> b) {
		return a.second > b.second;
		});
}

void LocalLeaderboard::sendScore(std::string name, float score)
{
	// Push the new score back to the vector in memory
	_scores.push_back(std::pair(name, score));
	std::sort(_scores.begin(), _scores.end(), [](std::pair<std::string, float> a, std::pair<std::string, float> b) {
		return a.second > b.second;
		});

	// Open the leaderboard file
	std::ofstream leaderboardFile(leaderboardFileName, std::ios::app);

	if (leaderboardFile.is_open()) {
		leaderboardFile << name << "=" << score << "\n";
		leaderboardFile.close();
	}

	std::string leaderboardString = "";

	// Limit the string to only show 10 scores
	for (size_t i = 0; i < std::min(_scores.size(), size_t(10)); i++)
	{
		leaderboardString += _scores[i].first + ": " + std::to_string((int)_scores[i].second) + "\n";
	}

	_leaderboardText.setString(leaderboardString);
}
