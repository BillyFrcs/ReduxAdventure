#pragma once

#ifndef PLAYER_HPP
	#define PLAYER_HPP

	#include <SFML/Graphics.hpp>
	#include <SFML/Graphics/Texture.hpp>
	#include <SFML/Graphics/Sprite.hpp>
	#include <SFML/System/Clock.hpp>

	#include "DefinitionsGame.hpp"

	#include "Collision/Collision.h"

	#include "./Game/Game.hpp"
	#include "./Platformer/Platformer.hpp"
	#include "./Enemy/Enemy.hpp"

class Entity;
class Platformer;
class Enemy;
class Enemies;

namespace Billy
{
class Player
{
public:
	Player();
	virtual ~Player();

public:
	void LoadPlayer();
	void PlayerAnimation();
	void PlayerStand();
	void PlayerWalk();
	void PlayerAttack();
	void PlayerAttackUltimate();
	void PlayerJump();
	void PlayerMovement(const float& MovementXOffset, const float& MovementYOffset);
	void PlayerJumpMovement();
	void PlayerController();
	void PlayerCollision();
	void ScaleFactorPlayer(const float FaceLeft, const float FaceRight);
	void HealthBarPlayer(sf::RenderTarget& Target);
	void PlayerGetDamage();
	void UpdateSoundJumpPlayer();
	void UpdateSoundFallPlayer();
	void UpdateSoundHitPlayer();

	virtual void DrawPlayer(sf::RenderWindow& Window) const;

public:
	const sf::Vector2f GetPlayerPosition() const;
	const sf::FloatRect GetPlayerBounds() const;

	sf::Vector3f& PlayerVelocity();

	sf::Sprite& PlayerSprite();

	std::vector<sf::Sprite> PlayerVec();

private:
	Entity* Entity_Object;
	Platformer* Platformer_Object;

private:
	sf::Sprite _maleCharacterSprite;
	sf::Clock _clockPlayer;

	sf::RectangleShape* _hpBarPlayerBackground;
	sf::RectangleShape* _hpBarPlayer;

	sf::Vector3f _playerVelocity;
	sf::Vector3f _playerJumpVelocity;

	sf::SoundBuffer _soundBufferJump;
	sf::SoundBuffer _soundBufferFall;
	sf::SoundBuffer _soundBufferHit;

	sf::Sound _soundJumpPlayer;
	sf::Sound _soundFallPlayer;
	sf::Sound _soundHitPlayer;

private:
	std::vector<sf::Sprite> _maleCharacterVec;

protected:
	// Player stand properties
	uint_fast32_t _frameStand;
	uint_fast32_t _rowStand;
	uint_fast32_t _frameAtStand;
	uint_fast32_t _frameCounterIteratorStand;

	// Player walk properties
	uint_fast32_t _frameWalk;
	uint_fast32_t _rowWalk;
	uint_fast32_t _frameAtWalk;
	uint_fast32_t _frameCounterIteratorWalk;

	// Player attack properties
	uint_fast32_t _frameAttack;
	uint_fast32_t _rowAttack;
	uint_fast32_t _frameAtAttack;
	uint_fast32_t _frameCounterIteratorAttack;

	// Player attack ultimate properties
	uint_fast32_t _frameAttackUltimate;
	uint_fast32_t _rowAttackUltimate;
	uint_fast32_t _frameAtAttackUltimate;
	uint_fast32_t _frameCounterIteratorAttackUltimate;

	// Player jump properties
	uint_fast32_t _frameJump;
	uint_fast32_t _rowJump;
	uint_fast32_t _frameAtJump;
	uint_fast32_t _frameCounterIteratorJump;

	// Player jump movement
	float _gravity;
	float _jumpSpeed;
	float _groundHeight;
	float _playerAnimationIterator;

	bool _isPlayerStand;
	bool _isPlayerGetDamage;

	// Damage player
	float _damagePlayer;
	float _damageUltimatePlayer;

	// Health player
	int _healthPlayer;
};
}

#endif // PLAYER_HPP