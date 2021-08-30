#include "Player.hpp"

#include <cmath>

static constexpr auto ITERATOR_STAND_SPEED = 3.0f;
static constexpr auto ITERATOR_WALK_SPEED = 6.0f;
static constexpr auto ITERATOR_ATTACK_SPEED = 3.5f;
static constexpr auto ITERATOR_ATTACK_ULTIMATE_SPEED = 3.5f;
static constexpr auto ITERATOR_JUMP_SPEED = 5.0f;
static constexpr auto ITERATOR_ANIMATION = 1.0f;

// Animation
enum Animation
{
	// Frame player stand
	FRAME_STAND = 0,	// Increase this value to go to the next frame
	ROW_STAND = 0,		// Increase this value to go to the next row
	FRAME_AT_STAND = 2, // Change this value to avoid a frame
	FRAME_COUNTER_ITERATOR_STAND = 0,

	// Frame player walk
	FRAME_WALK = 0,
	ROW_WALK = 4,
	FRAME_AT_WALK = 8,
	FRAME_COUNTER_ITERATOR_WALK = 0,

	// Frame player attack
	FRAME_ATTACK = 0,
	ROW_ATTACK = 3,
	FRAME_AT_ATTACK = 3,
	FRAME_COUNTER_ITERATOR_ATTACK = 0,

	// Frame player attack ultimate
	FRAME_ATTACK_ULTIMATE = 0,
	ROW_ATTACK_ULTIMATE = 1,
	FRAME_AT_ATTACK_ULTIMATE = 8,
	FRAME_COUNTER_ITERATOR_ATTACK_ULTIMATE = 0,

	// Frame player jump
	FRAME_JUMP = 3,
	ROW_JUMP = 0,
	FRAME_AT_JUMP = 4,
	FRAME_COUNTER_ITERATOR_JUMP = 0,
};

// Sprite sheet frame
enum Tux
{
	// Start from 1 frame
	FRAME = 1
};

Billy::Player::Player() :
	Entity_Object(),
	Platformer_Object(),
	_maleCharacterSprite(),
	_clockPlayer(),
	_playerVelocity(),
	_playerJumpVelocity(),
	_maleCharacterVec()
{
	// Player velocity
	this->_playerVelocity.x = 3.0f;
	this->_playerVelocity.y = 3.0f;

	// Player jump velocity
	this->_playerJumpVelocity.x = 0.0f;
	this->_playerJumpVelocity.y = 0.0f;
	this->_gravity = 1.0f;
	this->_jumpSpeed = 10.0f;
	this->_groundHeight = 500.f;

	this->_isPlayerStand = new bool(true);
	this->_isPlayerGetDamage = new bool(false);

	// Damage player
	this->_damagePlayer = 20.0f;
	this->_damageUltimatePlayer = 30.0f;

	// Health player
	this->_healthPlayer = 100;

	// Player animation iterator
	this->_playerAnimationIterator = static_cast<float>(ITERATOR_ANIMATION);

	// Initialise stand animation
	this->_frameStand = Animation::FRAME_STAND;
	this->_rowStand = Animation::ROW_STAND;
	this->_frameAtStand = Animation::FRAME_AT_STAND;
	this->_frameCounterIteratorStand = Animation::FRAME_COUNTER_ITERATOR_STAND;

	// Initialise walk animation
	this->_frameWalk = Animation::FRAME_WALK;
	this->_rowWalk = Animation::ROW_WALK;
	this->_frameAtWalk = Animation::FRAME_AT_WALK;
	this->_frameCounterIteratorWalk = Animation::FRAME_COUNTER_ITERATOR_WALK;

	// Initialise attack animation
	this->_frameAttack = Animation::FRAME_ATTACK;
	this->_rowAttack = Animation::ROW_ATTACK;
	this->_frameAtAttack = Animation::FRAME_AT_ATTACK;
	this->_frameCounterIteratorAttack = Animation::FRAME_COUNTER_ITERATOR_ATTACK;

	// Initialise attack ultimate animation
	this->_frameAttackUltimate = Animation::FRAME_ATTACK_ULTIMATE;
	this->_rowAttackUltimate = Animation::ROW_ATTACK_ULTIMATE;
	this->_frameAtAttackUltimate = Animation::FRAME_AT_ATTACK_ULTIMATE;
	this->_frameCounterIteratorAttackUltimate = Animation::FRAME_COUNTER_ITERATOR_ATTACK_ULTIMATE;

	// Initialise jump animation
	this->_frameJump = Animation::FRAME_JUMP;
	this->_rowJump = Animation::ROW_JUMP;
	this->_frameAtJump = Animation::FRAME_AT_JUMP;
	this->_frameCounterIteratorJump = Animation::FRAME_COUNTER_ITERATOR_JUMP;

	// Constructors class
	this->Entity_Object = new Entity();
	this->Platformer_Object = new Platformer();
}

Billy::Player::~Player()
{
}

void Billy::Player::LoadPlayer()
{
	const std::array<std::string, 5> name = { "Male Character Player" };

	// Male character player sprite
	static float scaleVectorX = 0.4f;

	static float scaleVectorY = 0.4f;

	this->Entity_Object->LoadTextureGame(name[0], MALE_CHARACTER_SHEET);

	this->_maleCharacterSprite.setTexture(this->Entity_Object->GetTextureGame(name[0]));
	this->_maleCharacterSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));
	this->_maleCharacterSprite.setPosition(sf::Vector2f(this->_maleCharacterSprite.getPosition().x + this->_maleCharacterSprite.getGlobalBounds().width / 3.3f, this->_maleCharacterSprite.getPosition().y + this->_maleCharacterSprite.getGlobalBounds().height / 1.0f));

	this->_maleCharacterVec.push_back(sf::Sprite(this->_maleCharacterSprite));

	this->PlayerCollision();
}

// Process all the player animation
void Billy::Player::PlayerAnimation()
{
	// Stand animation
	if (this->_isPlayerStand == true)
	{
		this->PlayerStand();
	}

	// Walk animation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->PlayerWalk();
		}
	}

	// Attack animation
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->PlayerAttack();
	}

	// Attack ultimate animation
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->PlayerAttackUltimate();
	}

	// Player jump animation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->PlayerJump();
	}
}

// Player stand animation
void Billy::Player::PlayerStand()
{
	this->_maleCharacterSprite.setTextureRect(sf::IntRect(192 * this->_frameStand, 256 * this->_rowStand, 192, 256));

	if (this->_clockPlayer.getElapsedTime().asSeconds() < this->_playerAnimationIterator)
	{
		if (this->_frameCounterIteratorStand == 60)
		{
			this->_frameStand = (this->_frameStand + Tux::FRAME) % this->_frameAtStand;

			this->_frameCounterIteratorStand = 0;
		}

		this->_frameCounterIteratorStand += ITERATOR_STAND_SPEED;
	}

	this->_clockPlayer.restart();
}

// Player walk animation
void Billy::Player::PlayerWalk()
{
	this->_maleCharacterSprite.setTextureRect(sf::IntRect(192 * this->_frameWalk, 257 * this->_rowWalk, 192, 256));

	if (this->_clockPlayer.getElapsedTime().asSeconds() < this->_playerAnimationIterator)
	{
		if (this->_frameCounterIteratorWalk == 60)
		{
			this->_frameWalk = (this->_frameWalk + Tux::FRAME) % this->_frameAtWalk;

			this->_frameCounterIteratorWalk = 0;
		}

		this->_frameCounterIteratorWalk += ITERATOR_WALK_SPEED;
	}

	this->_clockPlayer.restart();
}

// Player attack animation
void Billy::Player::PlayerAttack()
{
	this->_maleCharacterSprite.setTextureRect(sf::IntRect(192 * this->_frameAttack, 257 * this->_rowAttack, 192, 256));

	if (this->_clockPlayer.getElapsedTime().asSeconds() < this->_playerAnimationIterator)
	{
		if (this->_frameCounterIteratorAttack == 60)
		{
			this->_frameAttack = (this->_frameAttack + Tux::FRAME) % this->_frameAtAttack;

			this->_frameCounterIteratorAttack = 0;
		}

		this->_frameCounterIteratorAttack += ITERATOR_ATTACK_SPEED;
	}

	this->_clockPlayer.restart();
}

// Player attack ultimate animation
void Billy::Player::PlayerAttackUltimate()
{
	this->_maleCharacterSprite.setTextureRect(sf::IntRect(192 * this->_frameAttackUltimate, 257 * this->_rowAttackUltimate, 192, 256));

	if (this->_clockPlayer.getElapsedTime().asSeconds() < this->_playerAnimationIterator)
	{
		if (_frameCounterIteratorAttackUltimate == 60)
		{
			this->_frameAttackUltimate = (this->_frameAttackUltimate + Tux::FRAME) % this->_frameAtAttackUltimate;

			this->_frameCounterIteratorAttackUltimate = 0;
		}

		this->_frameCounterIteratorAttackUltimate += ITERATOR_ATTACK_ULTIMATE_SPEED;
	}

	this->_clockPlayer.restart();
}

// Player jump animation
void Billy::Player::PlayerJump()
{
	this->_maleCharacterSprite.setTextureRect(sf::IntRect(192 * this->_frameJump, 257 * this->_rowJump, 192, 256));

	if (this->_clockPlayer.getElapsedTime().asSeconds() < this->_playerAnimationIterator)
	{
		if (this->_frameCounterIteratorJump == 60)
		{
			this->_frameJump = (this->_frameJump + Tux::FRAME) % this->_frameAtJump;

			this->_frameCounterIteratorJump = 0;
		}

		this->_frameCounterIteratorJump += ITERATOR_JUMP_SPEED;
	}

	this->_clockPlayer.restart();
}

void Billy::Player::PlayerMovement(const float& MovementXOffset, const float& MovementYOffset)
{
	this->_maleCharacterSprite.move(sf::Vector2f(this->_playerVelocity.x * MovementXOffset, this->_playerVelocity.y * MovementYOffset));
}

void Billy::Player::PlayerJumpMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->_playerJumpVelocity.y = -this->_jumpSpeed;
	}
	else
	{
		this->_playerJumpVelocity.x = 0.0f;
	}

	if (this->GetPlayerPosition().y < this->_groundHeight || this->_playerJumpVelocity.y < 0.0f)
	{
		this->_playerJumpVelocity.y += this->_gravity;
	}
	else
	{
		this->_playerJumpVelocity.y = 0.0f;
	}

	this->_maleCharacterSprite.move(this->_playerJumpVelocity.x, this->_playerJumpVelocity.y);
}

void Billy::Player::ScaleFactorPlayer(const float FaceLeft, const float FaceRight)
{
	if (FaceLeft > 0.f || FaceRight > 0.f)
	{
		this->_maleCharacterSprite.setScale(FaceLeft, FaceRight);
	}
}

void Billy::Player::PlayerGetDamage()
{
	for (uint32_t player = 0; player < this->_maleCharacterVec.size(); player++)
	{
		this->_isPlayerGetDamage = new bool(true);

		if (this->_isPlayerGetDamage == true)
		{
			delete &this->_maleCharacterVec[player];

			delete &this->_maleCharacterSprite;

			this->_maleCharacterVec.erase(this->_maleCharacterVec.begin() + player);
		}
	}
}

void Billy::Player::UpdateSoundJumpPlayer()
{
	if (!this->_soundBufferJump.loadFromFile(PLAYER_JUMP_SOUND))
	{
		throw(std::runtime_error("Error loading sound").what());
	}

	this->_soundJumpPlayer.setBuffer(this->_soundBufferJump);

	this->_soundJumpPlayer.play();
}

void Billy::Player::UpdateSoundFallPlayer()
{
	if (!this->_soundBufferFall.loadFromFile(PLAYER_FALL_SOUND))
	{
		throw(std::runtime_error("Error loading sound").what());
	}

	this->_soundFallPlayer.setBuffer(this->_soundBufferFall);

	this->_soundFallPlayer.play();
}

void Billy::Player::UpdateSoundHitPlayer()
{
	if (!this->_soundBufferHit.loadFromFile(PLAYER_HIT_SOUND))
	{
		throw(std::runtime_error("Error loading sound").what());
	}

	this->_soundHitPlayer.setBuffer(this->_soundBufferHit);

	this->_soundHitPlayer.play();
}

void Billy::Player::PlayerController()
{

	// Movement speed player x and y offset
	static float xOffset = 1.0f;
	static float yOffset = 0.0f;

	// Rotate player face to left or right when key is pressed
	static float faceLeft = 1.0f;
	static float faceRight = 1.0f;

	// Scale vector
	static float scaleVectorX = 0.4f;
	static float scaleVectorY = 0.4f;

	/* Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->PlayerMovement(0.f, -1.f);

		this->PlayerWalk();
	}
	*/

	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->ScaleFactorPlayer(-faceLeft, faceRight);

		this->_maleCharacterSprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_maleCharacterSprite.setOrigin(this->GetPlayerBounds().width / 3.0f, 0.0f);

		this->PlayerMovement(-xOffset, yOffset);

		this->PlayerWalk();
	}

	/* Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->PlayerMovement(0.f, 1.f);

		this->PlayerWalk();
	}
	*/

	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->ScaleFactorPlayer(std::abs(faceLeft), std::abs(faceRight));

		this->_maleCharacterSprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_maleCharacterSprite.setOrigin(sf::Vector2f({ 0.0f, 0.0f }));

		this->PlayerMovement(xOffset, yOffset);

		this->PlayerWalk();
	}

	// Player attack
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->PlayerAttack();

		this->_damagePlayer = 20.0f;
	}

	// Player attack ultimate
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->PlayerAttackUltimate();

		this->_damageUltimatePlayer = 30.0f;
	}

	// Player jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->PlayerJumpMovement();

		this->UpdateSoundJumpPlayer();

		this->PlayerJump();
	}
}

// Player collision detection
void Billy::Player::PlayerCollision()
{
	float* collision = new float(0.0f);

	float* position = new float(0.0f);

	// Window left screen collision
	if (this->GetPlayerPosition().x < *collision)
	{
		this->_maleCharacterSprite.setPosition(*position, this->GetPlayerPosition().y);
	}

	// Window right screen collision
	if (this->GetPlayerPosition().x + this->GetPlayerBounds().width > SCREEN_WIDTH)
	{
		this->_maleCharacterSprite.setPosition(SCREEN_WIDTH - this->GetPlayerBounds().width, this->GetPlayerPosition().y);
	}

	// Window top collision
	if (this->GetPlayerPosition().y < *collision)
	{
		this->_maleCharacterSprite.setPosition(this->GetPlayerPosition().x, *position);
	}

	// Window bottom screen collision
	if (this->GetPlayerPosition().y + this->GetPlayerBounds().height > SCREEN_HEIGHT)
	{
		this->_maleCharacterSprite.setPosition(this->GetPlayerPosition().x, SCREEN_HEIGHT - this->GetPlayerBounds().height);
	}
}

void Billy::Player::HealthBarPlayer(sf::RenderTarget& Target)
{
	this->_hpBarPlayerBackground = new sf::RectangleShape();
	this->_hpBarPlayer = new sf::RectangleShape();

	sf::Vector3f hpBarPosition;

	hpBarPosition.x = 5.0f;
	hpBarPosition.y = 80.0f;

	sf::Vector3f hpBarSize;

	hpBarSize.x = 200.0f;
	hpBarSize.y = 30.0f;

	// HP bar player background
	this->_hpBarPlayerBackground->setSize(sf::Vector2f({ hpBarSize.x, hpBarSize.y }));
	this->_hpBarPlayerBackground->setFillColor(sf::Color({ 179, 181, 186 }));
	this->_hpBarPlayerBackground->setPosition(sf::Vector2f(hpBarPosition.x, hpBarPosition.y));

	// HP bar player
	this->_hpBarPlayer->setSize(sf::Vector2f({ hpBarSize.x, hpBarSize.y }));
	this->_hpBarPlayer->setFillColor(sf::Color({ 255, 255, 255 }));
	this->_hpBarPlayer->setPosition(sf::Vector2f(hpBarPosition.x, hpBarPosition.y));

	Target.draw(*this->_hpBarPlayerBackground);
	Target.draw(*this->_hpBarPlayer);
}

const sf::Vector2f Billy::Player::GetPlayerPosition() const
{
	return this->_maleCharacterSprite.getPosition();
}

const sf::FloatRect Billy::Player::GetPlayerBounds() const
{
	return this->_maleCharacterSprite.getGlobalBounds();
}

sf::Vector3f& Billy::Player::PlayerVelocity()
{
	return this->_playerVelocity;
}

sf::Sprite& Billy::Player::PlayerSprite()
{
	return this->_maleCharacterSprite;
}

std::vector<sf::Sprite> Billy::Player::PlayerVec()
{
	return this->_maleCharacterVec;
}

void Billy::Player::DrawPlayer(sf::RenderWindow& Window) const
{
	// Draw player character
	Window.draw(this->_maleCharacterSprite);
}