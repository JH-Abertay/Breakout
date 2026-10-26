#pragma once
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>


class LocalLeaderboard :
    public virtual Leaderboard
{
public:
    LocalLeaderboard(sf::RenderWindow* window);

    void retrieveScore() override;
    void sendScore(std::string name, float score) override;
};

