#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include "LocalLeaderboard.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _leaderboard(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _masterText(_font)
{
    if (!_font.openFromFile("font/montS.ttf")) {
    	std::cout << "ERROR: Failed to load font in GameManager";
    }
    _masterText.setPosition({50, 400});
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this);
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _leaderboard = new LocalLeaderboard(_window);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;


    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        handleEnterName();
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        handleEnterName();
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    _paddle->moveRight(dt);
    _paddle->moveLeft(dt);

    // update everything
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    if (_lives <= 0) {
        _leaderboard->retrieveScore();
    }

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
    if ((_levelComplete || _lives <= 0) && _nameEntered) {
        _leaderboard->render();
    }
}

void GameManager::levelComplete()
{
    _levelComplete = true;
    _leaderboard->retrieveScore();
}

void GameManager::handleEvent(sf::Event event)
{
    if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    	if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
	        _nameEntered = true;
	        _leaderboard->sendScore(_name, _score);
     	}
    }
    else if ((_levelComplete || _lives <= 0) && !_nameEntered) {
    	if (const sf::Event::TextEntered * textEntered = event.getIf<sf::Event::TextEntered>()) {
     		if (textEntered->unicode < 128) {
       			_name += static_cast<char>(textEntered->unicode);
          		if (_name.size() >= 10) {
	           		_nameEntered = true;
					_leaderboard->sendScore(_name, _score);
            	}
       		}
     	}
    }
}

void GameManager::handleEnterName()
{
    if (_nameEntered) {
        return;
    }

    _masterText.setString("Enter Name: " + _name);
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
void GameManager::addScore(float scoreToAdd){ _score += scoreToAdd; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
