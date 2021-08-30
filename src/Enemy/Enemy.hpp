#pragma once

#ifndef ENEMY_HPP
	#define ENEMY_HPP

	#include <SFML/Graphics.hpp>

	#include <vector>
	#include <chrono>
	#include <thread>

	#include "DefinitionsGame.hpp"

	#include "Collision/Collision.h"

	#include "./Game/Game.hpp"
	#include "./Player/Player.hpp"
	#include "./Entity/Entity.hpp"
	#include "./Platformer/Platformer.hpp"

class Entity;
class Platformer;
class Player;

namespace Billy
{
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

public:
	virtual void LoadEnemy() = 0;
	virtual void EnemyAnimation() = 0;
	virtual void EnemyWalk() = 0;
	virtual void EnemyAttack() = 0;
	virtual void EnemyMovement(const float& MovementXOffset, const float& MovementYOffset) = 0;
	virtual void EnemySpawning() = 0;
	virtual void EnemyAI() = 0;
	virtual void EnemyCollision() = 0;
	virtual void ScaleFactorEnemy(const float FaceLeft, const float FaceRight) = 0;
	virtual void EnemyGetDamage() = 0;

	virtual void DrawEnemy(sf::RenderWindow& Window) = 0;

protected:
	Entity* Entity_Object;
	Platformer* Platformer_Object;
	Player* Player_Object;

protected:
	sf::Clock _clockEnemy;
	sf::Vector3f _enemyVelocity;

	sf::Clock _enemySpawnTimer;
	sf::Int32 _enemySpawnTime;

protected:
	// Enemy walk properties
	uint_fast32_t _frameWalk;
	uint_fast32_t _rowWalk;
	uint_fast32_t _frameAtWalk;
	uint_fast32_t _frameCounterIteratorWalk;

	// Enemy attack properties
	uint_fast32_t _frameAttack;
	uint_fast32_t _rowAttack;
	uint_fast32_t _frameAtAttack;
	uint_fast32_t _frameCounterIteratorAttack;

	bool _isEnemyWalk;
	bool _isEnemyAttack;
	bool _isEnemyMove;
	bool _isEnemyGetDamage;

	// Enemy AI properties
	float _damageEnemy;
	float _enemyAnimationIterator;
};

// Enemies zombie and robot
class Enemies : public Enemy
{
public:
	Enemies();
	virtual ~Enemies();

public:
	void LoadEnemy() override;
	void EnemyAnimation() override;
	void EnemyWalk() override;
	void EnemyAttack() override;
	void EnemyMovement(const float& MovementXOffset, const float& MovementYOffset) override;
	void EnemySpawning() override;
	void EnemyAI() override;
	void EnemyCollision() override;
	void ScaleFactorEnemy(const float FaceLeft, const float FaceRight) override;
	void EnemyGetDamage() override;

	void DrawEnemy(sf::RenderWindow& Window) override;

public:
	// Zombie
	const sf::Vector2f GetEnemyZombiePosition() const;
	const sf::FloatRect GetEnemyZombieBounds() const;
	const sf::Sprite& EnemyZombieSprite() const;

	std::vector<sf::Sprite> EnemyZombieVec();

	// Robot
	const sf::Vector2f GetEnemyRobotPosition() const;
	const sf::FloatRect GetEnemyRobotBounds() const;
	const sf::Sprite& EnemyRobotSprite() const;

	std::vector<sf::Sprite> EnemyRobotVec();

	// Male
	const sf::Vector2f GetEnemyMalePosition() const;
	const sf::FloatRect GetEnemyMaleBounds() const;
	const sf::Sprite& EnemyMaleSprite() const;

	std::vector<sf::Sprite> EnemyMaleVec();

private:
	sf::Sprite _zombieEnemySprite;
	sf::Sprite _robotEnemySprite;
	sf::Sprite _maleEnemySprite;

protected:
	std::vector<sf::Sprite> _zombieEnemyVec;
	std::vector<sf::Sprite> _robotEnemyVec;
	std::vector<sf::Sprite> _maleEnemyVec;
};
}

#endif // ENEMY_HPP