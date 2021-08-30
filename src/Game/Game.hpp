#pragma once

#ifndef GAME_HPP
	#define GAME_HPP

	#include <SFML/Graphics.hpp>

	#include <string>
	#include <memory>

	#include "DefinitionsGame.hpp"

	#include "Platform/Platform.hpp"

	#include "./Entity/Entity.hpp"
	#include "./Player/Player.hpp"
	#include "./Platformer/Platformer.hpp"
	#include "./Enemy/Enemy.hpp"

class Player;
class Platformer;
class Enemy;
class Enemies;
class Entity;

namespace Billy
{
class Game
{
public:
	Game(const float& ScreenWidth, const float& ScreenHeight, const std::string& GameTitle);
	virtual ~Game();

public:
	virtual void ViewGame();
	virtual void GameLoop();
	virtual void RunGame();

private:
	Platformer* Platformer_Object;
	Player* Player_Object;
	Enemies* Enemies_Object;
	Entity* Entity_Object;

private:
	util::Platform _platform;

private:
	sf::RenderWindow _window;
	sf::ContextSettings _antiAliasing;
	sf::Event _event;
	sf::View _view;

	sf::Clock _clockFrameRate;
	sf::Time _timeFrameRate;

protected:
	float _frameRate;

	bool _isPlayerSpawn;
	bool _isGamePlay;
	bool _isPlayerAttack;
};
}

#endif // GAME_HPP