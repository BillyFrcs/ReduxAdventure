#include "Game.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>

Billy::Game::Game(const float& ScreenWidth, const float& ScreenHeight, const std::string& GameTitle) :
	Platformer_Object(),
	Player_Object(),
	Enemies_Object(),
	Entity_Object(),
	_platform(),
	_window(),
	_antiAliasing(),
	_event(),
	_view(),
	_deltaTimeClock(),
	_clockFrameRate(),
	_timeFrameRate(),
	_deltaTime(),
	_frameRate()
{
#if defined(_DEBUG)
	std::cout << "Billy Games | Redux Adventure" << std::endl;
#endif

	std::srand(static_cast<unsigned int>(time(NULL)));

	// In Windows at least, this must be called before creating the window
	static float screenScalingFactor = this->_platform.getScreenScalingFactor(this->_window.getSystemHandle());

	// Setting antiAliasing level
	this->_antiAliasing.antialiasingLevel = 8;

	// Use the screenScalingFactor
	this->_window.create(sf::VideoMode((ScreenWidth * screenScalingFactor), (ScreenHeight * screenScalingFactor)), GameTitle, sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar /*, this->_antiAliasing*/);

	// this->_window.setVerticalSyncEnabled(true);

	// this->_window.setFramerateLimit(60);

	this->_window.setKeyRepeatEnabled(false);

	this->_platform.setIcon(this->_window.getSystemHandle());

	// Set delta time per frame
	this->_deltaTime = (1.f / 60.f);

	this->_isPlayerSpawn = new bool(true);
	this->_isGamePlay = new bool(true);

	// Constructors class
	this->Platformer_Object = new Platformer();
	this->Player_Object = new Player();
	this->Enemies_Object = new Enemies();
	this->Entity_Object = new Entity();
}

Billy::Game::~Game()
{
}

void Billy::Game::ViewGame()
{
	// View game
	this->_view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));

	this->_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::Vector2f playerPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

	if (this->Player_Object->GetPlayerPosition().x + 10.f > (SCREEN_WIDTH / 2.f))
	{
		playerPosition.x = this->Player_Object->GetPlayerPosition().x + 10.f;
	}
	else
	{
		playerPosition.x = (SCREEN_WIDTH / 2.f);
	}

	this->_view.setCenter(playerPosition);

	// this->_window.setView(this->_view);
}

void Billy::Game::GameLoop()
{
	// Playing sound game
	if (this->_isPlayerSpawn == true)
	{
		this->Entity_Object->SoundPlayerSpawn();
	}

	if (this->_isGamePlay == true)
	{
		this->Entity_Object->SoundGamePlay();
	}

	// Load texture platformer game
	this->Platformer_Object->LoadPlatformerGame();

	this->Player_Object->LoadPlayer();

	this->Enemies_Object->LoadEnemy();

	this->Player_Object->PlayerAnimation();

	this->Enemies_Object->EnemyAnimation();

	while (this->_window.isOpen())
	{
		// Dealing with events delta time
		this->_deltaTimeClock.getElapsedTime().asSeconds();

		this->_deltaTime = this->_deltaTimeClock.restart().asSeconds();

		while (this->_window.pollEvent(this->_event))
		{
			switch (this->_event.type)
			{
				case sf::Event::Closed:
					this->_window.close();
					break;

				case sf::Event::KeyPressed: {
					switch (this->_event.key.code)
					{
						case sf::Keyboard::Escape:
							this->_window.close();
							break;

						default:
							break;
					}
				}
				break;

				default:
					break;
			}

			if (this->_event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0.f, 0.f, this->_event.size.width, this->_event.size.height);

				this->_window.setView(sf::View(visibleArea));
			}
		}

		this->_timeFrameRate = this->_clockFrameRate.getElapsedTime();

		this->_frameRate = 1.0f / _timeFrameRate.asSeconds();

		// Flooring it will make the frame rate a rounded number
		// std::cerr << "FPS: " << std::floor(this->_frameRate) << std::endl; // DEBUG

		this->_clockFrameRate.restart().asSeconds();

		this->Player_Object->PlayerCollision();

		this->Enemies_Object->EnemyCollision();

		// Enemy zombie collision with player
		if (Collision::PixelPerfectTest(this->Player_Object->PlayerSprite(), this->Enemies_Object->EnemyZombieSprite()) == true)
		{
			// std::cerr << "Collision enemy zombie \n"; // DEBUG

			//Bottom collision
			if (this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyZombieBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height < this->Enemies_Object->GetEnemyZombieBounds().top + this->Enemies_Object->GetEnemyZombieBounds().height
				&& this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyZombieBounds().left + this->Enemies_Object->GetEnemyZombieBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyZombieBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyZombieBounds().top - this->Player_Object->GetPlayerBounds().height);
				}
			}

			//Top collision
			else if (this->Player_Object->GetPlayerBounds().top > Enemies_Object->GetEnemyZombieBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > Enemies_Object->GetEnemyZombieBounds().top + Enemies_Object->GetEnemyZombieBounds().height
				&& this->Player_Object->GetPlayerBounds().left < Enemies_Object->GetEnemyZombieBounds().left + this->Enemies_Object->GetEnemyZombieBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyZombieBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyZombieBounds().top + this->Enemies_Object->GetEnemyZombieBounds().height);
				}
			}

			//Right collision
			if (this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyZombieBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width < this->Enemies_Object->GetEnemyZombieBounds().left + this->Enemies_Object->GetEnemyZombieBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyZombieBounds().top + this->Enemies_Object->GetEnemyZombieBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyZombieBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyZombieBounds().left - this->Player_Object->GetPlayerBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}

			//Left collision
			else if (this->Player_Object->GetPlayerBounds().left > this->Enemies_Object->GetEnemyZombieBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyZombieBounds().left + this->Enemies_Object->GetEnemyZombieBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyZombieBounds().top + this->Enemies_Object->GetEnemyZombieBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyZombieBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyZombieBounds().left + this->Enemies_Object->GetEnemyZombieBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}
		}
		else
		{
			// std::cout << "No collision enemy zombie \n"; // DEBUG
		}

		// Enemy robot collision with player
		if (Collision::PixelPerfectTest(this->Player_Object->PlayerSprite(), this->Enemies_Object->EnemyRobotSprite()) == true)
		{
			// std::cerr << "Collision enemy robot \n"; // DEBUG

			//Bottom collision
			if (this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyRobotBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height < this->Enemies_Object->GetEnemyRobotBounds().top + this->Enemies_Object->GetEnemyRobotBounds().height
				&& this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyRobotBounds().left + this->Enemies_Object->GetEnemyRobotBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyRobotBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyRobotBounds().top - this->Player_Object->GetPlayerBounds().height);
				}
			}

			//Top collision
			else if (this->Player_Object->GetPlayerBounds().top > Enemies_Object->GetEnemyRobotBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > Enemies_Object->GetEnemyRobotBounds().top + Enemies_Object->GetEnemyRobotBounds().height
				&& this->Player_Object->GetPlayerBounds().left < Enemies_Object->GetEnemyRobotBounds().left + this->Enemies_Object->GetEnemyRobotBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyRobotBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyRobotBounds().top + this->Enemies_Object->GetEnemyRobotBounds().height);
				}
			}

			//Right collision
			if (this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyRobotBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width < this->Enemies_Object->GetEnemyRobotBounds().left + this->Enemies_Object->GetEnemyRobotBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyRobotBounds().top + this->Enemies_Object->GetEnemyRobotBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyRobotBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyRobotBounds().left - this->Player_Object->GetPlayerBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}

			//Left collision
			else if (this->Player_Object->GetPlayerBounds().left > this->Enemies_Object->GetEnemyRobotBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyRobotBounds().left + this->Enemies_Object->GetEnemyRobotBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyRobotBounds().top + this->Enemies_Object->GetEnemyRobotBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyRobotBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyRobotBounds().left + this->Enemies_Object->GetEnemyRobotBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}
		}
		else
		{
			// std::cout << "No collision enemy robot \n"; // DEBUG
		}

		// Enemy male collision with player
		if (Collision::PixelPerfectTest(this->Player_Object->PlayerSprite(), this->Enemies_Object->EnemyMaleSprite()) == true)
		{
			// std::cerr << "Collision enemy robot \n"; // DEBUG

			//Bottom collision
			if (this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyMaleBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height < this->Enemies_Object->GetEnemyMaleBounds().top + this->Enemies_Object->GetEnemyMaleBounds().height
				&& this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyMaleBounds().left + this->Enemies_Object->GetEnemyMaleBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyMaleBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyMaleBounds().top - this->Player_Object->GetPlayerBounds().height);
				}
			}

			//Top collision
			else if (this->Player_Object->GetPlayerBounds().top > Enemies_Object->GetEnemyMaleBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > Enemies_Object->GetEnemyMaleBounds().top + Enemies_Object->GetEnemyMaleBounds().height
				&& this->Player_Object->GetPlayerBounds().left < Enemies_Object->GetEnemyMaleBounds().left + this->Enemies_Object->GetEnemyMaleBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyMaleBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Enemies_Object->GetEnemyMaleBounds().top + this->Enemies_Object->GetEnemyMaleBounds().height);
				}
			}

			//Right collision
			if (this->Player_Object->GetPlayerBounds().left < this->Enemies_Object->GetEnemyMaleBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width < this->Enemies_Object->GetEnemyMaleBounds().left + this->Enemies_Object->GetEnemyMaleBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyMaleBounds().top + this->Enemies_Object->GetEnemyMaleBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyMaleBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyMaleBounds().left - this->Player_Object->GetPlayerBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}

			//Left collision
			else if (this->Player_Object->GetPlayerBounds().left > this->Enemies_Object->GetEnemyMaleBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Enemies_Object->GetEnemyMaleBounds().left + this->Enemies_Object->GetEnemyMaleBounds().width
				&& this->Player_Object->GetPlayerBounds().top < this->Enemies_Object->GetEnemyMaleBounds().top + this->Enemies_Object->GetEnemyMaleBounds().height)
			{
				if (this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Enemies_Object->GetEnemyMaleBounds().top)
				{
					this->Player_Object->PlayerVelocity().x = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Enemies_Object->GetEnemyMaleBounds().left + this->Enemies_Object->GetEnemyMaleBounds().width, this->Player_Object->GetPlayerBounds().top);
				}
			}
		}
		else
		{
			// std::cout << "No collision enemy robot \n"; // DEBUG
		}

		/* Ground collision with player
		if (Collision::PixelPerfectTest(this->Player_Object->PlayerSprite(), this->Platformer_Object->GroundSprite()) == true)
		{
			// std::cerr << "Collision ground \n"; // DEBUG

			//Bottom collision
			if (this->Player_Object->GetPlayerBounds().top < this->Platformer_Object->GetGroundBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height < this->Platformer_Object->GetGroundBounds().top + this->Platformer_Object->GetGroundBounds().height
				&& this->Player_Object->GetPlayerBounds().left < this->Platformer_Object->GetGroundBounds().left + this->Platformer_Object->GetGroundBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Platformer_Object->GetGroundBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Platformer_Object->GetGroundBounds().top - this->Player_Object->GetPlayerBounds().height);
				}
			}

			// Top collision
			else if (this->Player_Object->GetPlayerBounds().top > this->Platformer_Object->GetGroundBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Platformer_Object->GetGroundBounds().top + this->Platformer_Object->GetGroundBounds().height
				&& this->Player_Object->GetPlayerBounds().left < this->Platformer_Object->GetGroundBounds().left + this->Platformer_Object->GetGroundBounds().width)
			{
				if (this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Platformer_Object->GetGroundBounds().left)
				{
					this->Player_Object->PlayerVelocity().y = 0.0f;

					this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Platformer_Object->GetGroundBounds().top + this->Platformer_Object->GetGroundBounds().height);
				}
			}

			// Right collision
			if (this->Player_Object->GetPlayerBounds().left < this->Platformer_Object->GetGroundBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width < this->Platformer_Object->GetGroundBounds().left + this->Platformer_Object->GetGroundBounds().width
				&& this->Player_Object->GetPlayerBounds().top<this->Platformer_Object->GetGroundBounds().top + this->Platformer_Object->GetGroundBounds().height&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height> this->Platformer_Object->GetGroundBounds().top)
			{
				this->Player_Object->PlayerVelocity().x = 0.0f;

				this->Player_Object->PlayerSprite().setPosition(this->Platformer_Object->GetGroundBounds().left - this->Player_Object->GetPlayerBounds().width, this->Player_Object->GetPlayerBounds().top);
			}

			//Left collision
			else if (this->Player_Object->GetPlayerBounds().left > this->Platformer_Object->GetGroundBounds().left
				&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width > this->Platformer_Object->GetGroundBounds().left + this->Platformer_Object->GetGroundBounds().width
				&& this->Player_Object->GetPlayerBounds().top<this->Platformer_Object->GetGroundBounds().top + this->Platformer_Object->GetGroundBounds().height&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height> this->Platformer_Object->GetGroundBounds().top)
			{
				this->Player_Object->PlayerVelocity().x = 0.0f;

				this->Player_Object->PlayerSprite().setPosition(this->Platformer_Object->GetGroundBounds().left + this->Platformer_Object->GetGroundBounds().width, this->Player_Object->GetPlayerBounds().top);
			}
		}
		else
		{
			// std::cout << "No collision ground \n"; // DEBUG
		}

		// Trees rocks collision with player
		if (Collision::PixelPerfectTest(this->Player_Object->PlayerSprite(), this->Platformer_Object->RocksTreesSprite()) == true)
		{
			// std::cerr << "Collision rocks trees \n"; // DEBUG

			//Bottom collision
			if (this->Player_Object->GetPlayerBounds().top < this->Platformer_Object->GetRocksTreesBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height < this->Platformer_Object->GetRocksTreesBounds().top + this->Platformer_Object->GetRocksTreesBounds().height
				&& this->Player_Object->GetPlayerBounds().left<this->Platformer_Object->GetRocksTreesBounds().left + this->Platformer_Object->GetRocksTreesBounds().width&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width> this->Platformer_Object->GetRocksTreesBounds().left)
			{
				this->Player_Object->PlayerVelocity().y = 0.0f;

				this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Platformer_Object->GetRocksTreesBounds().top - this->Player_Object->GetPlayerBounds().height);
			}

			//Top collision
			else if (this->Player_Object->GetPlayerBounds().top > this->Platformer_Object->GetRocksTreesBounds().top
				&& this->Player_Object->GetPlayerBounds().top + this->Player_Object->GetPlayerBounds().height > this->Platformer_Object->GetRocksTreesBounds().top + this->Platformer_Object->GetRocksTreesBounds().height
				&& this->Player_Object->GetPlayerBounds().left<this->Platformer_Object->GetRocksTreesBounds().left + this->Platformer_Object->GetRocksTreesBounds().width&& this->Player_Object->GetPlayerBounds().left + this->Player_Object->GetPlayerBounds().width> this->Platformer_Object->GetRocksTreesBounds().left)
			{
				this->Player_Object->PlayerVelocity().y = 0.0f;

				this->Player_Object->PlayerSprite().setPosition(this->Player_Object->GetPlayerBounds().left, this->Platformer_Object->GetRocksTreesBounds().top + this->Platformer_Object->GetRocksTreesBounds().height);
			}
		}
		else
		{
			// std::cout << "No collision rocks trees \n"; // DEBUG
		}
		*/

		// Player object
		this->Player_Object->PlayerAnimation();

		this->Player_Object->PlayerController();

		this->Player_Object->PlayerJumpMovement();

		// Enemy object
		this->Enemies_Object->EnemyAnimation();

		this->Enemies_Object->EnemyAI();

		// View game
		this->ViewGame();

		this->_window.clear(sf::Color::White);

		// Render game
		this->Platformer_Object->DrawPlatformer(this->_window);

		this->Player_Object->HealthBarPlayer(this->_window);

		this->Enemies_Object->DrawEnemy(this->_window);

		this->Player_Object->DrawPlayer(this->_window);

		// Get the FPS game
		this->Platformer_Object->GetFPSGame(std::floor(this->_frameRate));

		this->_window.setKeyRepeatEnabled(false);

		this->_window.display();
	}
}

void Billy::Game::RunGame()
{
	// Run the game loop
	this->GameLoop();
}