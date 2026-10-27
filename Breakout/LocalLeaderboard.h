#pragma once
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <string>

// An instance of leaderboard which saves scores to local disk.
class LocalLeaderboard :
    public virtual Leaderboard
{
public:
    LocalLeaderboard(sf::RenderWindow* window);
    ~LocalLeaderboard();

    // Retrieve scores from file and places them in memory.
    void retrieveScore() override;
    // Save the score to file, and add to the memory leaderboard file.
    void sendScore(std::string name, float score) override;
private:
    // Name of file used to save the leaderboard to.
    std::string leaderboardFileName = "leaderboard.txt";
};

