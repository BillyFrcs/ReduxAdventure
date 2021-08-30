#include "Enemy.hpp"

static constexpr auto ITERATOR_WALK_SPEED = 6.0f;
static constexpr auto ITERATOR_ATTACK_SPEED = 3.0f;
static constexpr auto ITERATOR_ANIMATION = 1.0f;

// Animation
enum Animation
{
	// Frame player walk
	FRAME_WALK = 0,	   // Increase this value to go to the next frame
	ROW_WALK = 4,	   // Increase this value to go to the next row
	FRAME_AT_WALK = 8, // Change this value to avoid a frame
	FRAME_COUNTER_ITERATOR_WALK = 0,

	// Frame player attack
	FRAME_ATTACK = 0,
	ROW_ATTACK = 3,
	FRAME_AT_ATTACK = 3,
	FRAME_COUNTER_ITERATOR_ATTACK = 0,
};

// Sprite sheet frame
enum Tux
{
	// Start from 1 frame
	FRAME = 1
};

Billy::Enemy::Enemy() :
	Entity_Object(),
	Platformer_Object(),
	Player_Object(),
	_clockEnemy(),
	_enemyVelocity()
{
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

	// Constructor class
	this->Entity_Object = new Entity();
	this->Platformer_Object = new Platformer();
	this->Player_Object = new Player();
}

Billy::Enemy::~Enemy()
{
}

Billy::Enemies::Enemies()
{
	// Enemy velocity
	this->_enemyVelocity.x = 1.0f;
	this->_enemyVelocity.y = 1.0f;

	// Enemy bool
	this->_isEnemyWalk = new bool(true);
	this->_isEnemyAttack = new bool(true);
	this->_isEnemyMove = new bool(true);
	this->_isEnemyGetDamage = new bool(true);

	//Enemy damage
	this->_damageEnemy = 10.0f;

	// Enemy spawn timer
	this->_enemySpawnTimer.restart();
	this->_enemySpawnTime = 20;

	// Enemy animation iterator
	this->_enemyAnimationIterator = static_cast<float>(ITERATOR_ANIMATION);
}

Billy::Enemies::~Enemies()
{
}

// ===========================================================
// Enemy zombie and robot
// ===========================================================
void Billy::Enemies::LoadEnemy()
{
	const std::array<std::string, 5> name = { "Zombie Enemy", "Robot Enemy", "Male Enemy" };

	// Zombie enemy scale vector
	static float scaleVectorX = 0.4f;
	static float scaleVectorY = 0.4f;

	// Zombie enemy face scale
	static float faceLeft = 1.0f;
	static float faceRight = 1.0f;

	// Zombie enemy
	this->Entity_Object->LoadTextureGame(name[0], ZOMBIE_ENEMY_SHEET);
	this->_zombieEnemySprite.setTexture(this->Entity_Object->GetTextureGame(name[0]));
	this->_zombieEnemySprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));
	this->_zombieEnemySprite.scale(sf::Vector2f({ -faceLeft, faceRight }));
	this->_zombieEnemySprite.setPosition(sf::Vector2f(this->_zombieEnemySprite.getPosition().x + this->_zombieEnemySprite.getGlobalBounds().width + 900.0f, this->_zombieEnemySprite.getPosition().y + this->_zombieEnemySprite.getGlobalBounds().height / 1.0f));

	this->_zombieEnemyVec.push_back(sf::Sprite(this->_zombieEnemySprite));

	// Robot enemy
	this->Entity_Object->LoadTextureGame(name[1], ROBOT_ENEMY_SHEET);

	this->_robotEnemySprite.setTexture(this->Entity_Object->GetTextureGame(name[1]));
	this->_robotEnemySprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));
	this->_robotEnemySprite.scale(sf::Vector2f({ -faceLeft, faceRight }));
	this->_robotEnemySprite.setPosition(sf::Vector2f(this->_robotEnemySprite.getPosition().x + this->_robotEnemySprite.getGlobalBounds().width + 600.0f, this->_robotEnemySprite.getPosition().y + this->_robotEnemySprite.getGlobalBounds().height / 1.0f));

	this->_robotEnemyVec.push_back(sf::Sprite(this->_robotEnemySprite));

	// Male enemy
	this->Entity_Object->LoadTextureGame(name[2], MALE_ENEMY_SHEET);

	this->_maleEnemySprite.setTexture(this->Entity_Object->GetTextureGame(name[2]));
	this->_maleEnemySprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));
	this->_maleEnemySprite.scale(sf::Vector2f({ -faceLeft, faceRight }));
	this->_maleEnemySprite.setPosition(sf::Vector2f(this->_maleEnemySprite.getPosition().x + this->_maleEnemySprite.getGlobalBounds().width + 750.0f, this->_maleEnemySprite.getPosition().y + this->_maleEnemySprite.getGlobalBounds().height / 1.0f));

	this->_maleEnemyVec.push_back(sf::Sprite(this->_maleEnemySprite));
}

// Process all the enemy animation
void Billy::Enemies::EnemyAnimation()
{
	// Walk animation
	if (this->_isEnemyWalk == true)
	{
		this->EnemyWalk();
	}

	// Attack animation
	if (this->_isEnemyAttack == true)
	{
		this->EnemyAttack();
	}
}

// Enemy walk animation
void Billy::Enemies::EnemyWalk()
{
	if (this->_isEnemyWalk == true)
	{
		this->_zombieEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameWalk, 257 * this->_rowWalk, 192, 256));
	}

	if (this->_isEnemyWalk == true)
	{
		this->_robotEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameWalk, 257 * this->_rowWalk, 192, 256));
	}

	if (this->_isEnemyWalk == true)
	{
		this->_maleEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameWalk, 257 * this->_rowWalk, 192, 256));
	}

	if (this->_clockEnemy.getElapsedTime().asSeconds() < this->_enemyAnimationIterator)
	{
		if (this->_frameCounterIteratorWalk == 60)
		{
			this->_frameWalk = (this->_frameWalk + Tux::FRAME) % this->_frameAtWalk;

			this->_frameCounterIteratorWalk = 0;
		}

		this->_frameCounterIteratorWalk += ITERATOR_WALK_SPEED;
	}

	this->_clockEnemy.restart();
}

// Enemy attack animation
void Billy::Enemies::EnemyAttack()
{
	if (this->_isEnemyAttack == true)
	{
		this->_zombieEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameAttack, 257 * this->_rowAttack, 192, 256));
	}

	if (this->_isEnemyAttack == true)
	{
		this->_robotEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameAttack, 257 * this->_rowAttack, 192, 256));
	}

	if (this->_isEnemyAttack == true)
	{
		this->_maleEnemySprite.setTextureRect(sf::IntRect(192 * this->_frameAttack, 257 * this->_rowAttack, 192, 256));
	}

	if (this->_clockEnemy.getElapsedTime().asSeconds() < this->_enemyAnimationIterator)
	{
		if (this->_frameCounterIteratorAttack == 60)
		{
			this->_frameAttack = (this->_frameAttack + Tux::FRAME) % this->_frameAtAttack;

			this->_frameCounterIteratorAttack = 0;
		}

		this->_frameCounterIteratorAttack += ITERATOR_ATTACK_SPEED;
	}

	this->_clockEnemy.restart();
}

void Billy::Enemies::EnemyMovement(const float& MovementXOffset, const float& MovementYOffset)
{
	if (!this->_isEnemyMove != true)
	{
		this->_zombieEnemySprite.move(sf::Vector2f(this->_enemyVelocity.x * MovementXOffset, this->_enemyVelocity.y * MovementYOffset));
	}

	if (!this->_isEnemyMove != true)
	{
		this->_robotEnemySprite.move(sf::Vector2f(this->_enemyVelocity.x * MovementXOffset, this->_enemyVelocity.y * MovementYOffset));
	}

	if (!this->_isEnemyMove != true)
	{
		this->_maleEnemySprite.move(sf::Vector2f(this->_enemyVelocity.x * MovementXOffset, this->_enemyVelocity.y * MovementYOffset));
	}
}

void Billy::Enemies::ScaleFactorEnemy(const float FaceLeft, const float FaceRight)
{
	if (FaceLeft > 0.f || FaceRight > 0.f)
	{
		this->_zombieEnemySprite.setScale(FaceLeft, FaceRight);

		this->_robotEnemySprite.setScale(FaceLeft, FaceRight);

		this->_maleEnemySprite.setScale(FaceLeft, FaceRight);
	}
}

void Billy::Enemies::EnemySpawning()
{
}

void Billy::Enemies::EnemyGetDamage()
{
	for (uint32_t enemyZombie = 0; enemyZombie < this->_zombieEnemyVec.size(); enemyZombie++)
	{
		if (this->_isEnemyGetDamage == true)
		{
			delete &this->_zombieEnemySprite;

			delete &this->_zombieEnemyVec[enemyZombie];

			this->_zombieEnemyVec.erase(this->_zombieEnemyVec.begin() + enemyZombie);
		}
	}

	for (uint32_t enemyRobot = 0; enemyRobot < this->_robotEnemyVec.size(); enemyRobot++)
	{
		if (this->_isEnemyGetDamage == true)
		{
			delete &this->_robotEnemySprite;

			delete &this->_robotEnemyVec[enemyRobot];

			this->_robotEnemyVec.erase(this->_robotEnemyVec.begin() + enemyRobot);
		}
	}

	for (uint32_t enemyMale = 0; enemyMale < this->_robotEnemyVec.size(); enemyMale++)
	{
		if (this->_isEnemyGetDamage == true)
		{
			delete &this->_maleEnemySprite;

			delete &this->_maleEnemyVec[enemyMale];

			this->_robotEnemyVec.erase(this->_robotEnemyVec.begin() + enemyMale);
		}
	}
}

void Billy::Enemies::EnemyAI()
{
	// Movement speed zombie enemy x and y offset
	static float xOffset = 1.0f;
	static float yOffset = 0.0f;

	// Rotate zombie enemy face to left or right when key is pressed
	static float faceLeft = 1.0f;
	static float faceRight = 1.0f;

	// Scale vector
	static float scaleVectorX = 0.4f;
	static float scaleVectorY = 0.4f;

	// Enemy movement
	const float movement = 1.0f;

	// Left
	if (this->_enemyVelocity.x >= static_cast<float>(movement))
	{
		this->ScaleFactorEnemy(-faceLeft, faceRight);

		this->_zombieEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_robotEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_maleEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->EnemyMovement(-xOffset, yOffset);

		this->EnemyWalk();
	}

	// Right
	if (this->_enemyVelocity.x < static_cast<float>(movement))
	{
		this->ScaleFactorEnemy(std::abs(faceLeft), std::abs(faceRight));

		this->_zombieEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_robotEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->_maleEnemySprite.scale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

		this->EnemyMovement(xOffset, yOffset);

		this->EnemyWalk();
	}

	// Enemy attack
	if (Collision::PixelPerfectTest(this->EnemyZombieSprite(), this->Player_Object->PlayerSprite()))
	{
		this->EnemyAttack();

		this->_damageEnemy = 10.0f;
	}
}

void Billy::Enemies::EnemyCollision()
{
	float* collision = new float(0.0f);

	float* position = new float(0.0f);

	// Window left screen collision
	if (this->GetEnemyZombiePosition().x < *collision)
	{
		this->_zombieEnemySprite.setPosition(*position, this->GetEnemyZombiePosition().y);
	}

	// Window top collision
	if (this->GetEnemyZombiePosition().y < *collision)
	{
		this->_zombieEnemySprite.setPosition(this->GetEnemyZombiePosition().x, *position);
	}

	// Window bottom screen collision
	if (this->GetEnemyZombiePosition().y + this->GetEnemyZombieBounds().height > SCREEN_HEIGHT)
	{
		this->_zombieEnemySprite.setPosition(this->GetEnemyZombiePosition().x, SCREEN_HEIGHT - this->GetEnemyZombieBounds().height);
	}
}

// Zombie
const sf::Vector2f Billy::Enemies::GetEnemyZombiePosition() const
{
	return this->_zombieEnemySprite.getPosition();
}

const sf::FloatRect Billy::Enemies::GetEnemyZombieBounds() const
{
	return this->_zombieEnemySprite.getGlobalBounds();
}

const sf::Sprite& Billy::Enemies::EnemyZombieSprite() const
{
	return this->_zombieEnemySprite;
}

std::vector<sf::Sprite> Billy::Enemies::EnemyZombieVec()
{
	return this->_zombieEnemyVec;
}

// Robot
const sf::Vector2f Billy::Enemies::GetEnemyRobotPosition() const
{
	return this->_robotEnemySprite.getPosition();
}

const sf::FloatRect Billy::Enemies::GetEnemyRobotBounds() const
{
	return this->_robotEnemySprite.getGlobalBounds();
}

const sf::Sprite& Billy::Enemies::EnemyRobotSprite() const
{
	return this->_robotEnemySprite;
}

std::vector<sf::Sprite> Billy::Enemies::EnemyRobotVec()
{
	return this->_robotEnemyVec;
}

// Male
const sf::Vector2f Billy::Enemies::GetEnemyMalePosition() const
{
	return this->_maleEnemySprite.getPosition();
}

const sf::FloatRect Billy::Enemies::GetEnemyMaleBounds() const
{
	return this->_maleEnemySprite.getGlobalBounds();
}

const sf::Sprite& Billy::Enemies::EnemyMaleSprite() const
{
	return this->_maleEnemySprite;
}

std::vector<sf::Sprite> Billy::Enemies::EnemyMaleVec()
{
	return this->_maleEnemyVec;
}

void Billy::Enemies::DrawEnemy(sf::RenderWindow& Window)
{
	// Draw enemy zombie and robot
	Window.draw(this->_zombieEnemySprite);

	Window.draw(this->_robotEnemySprite);

	Window.draw(this->_maleEnemySprite);
}