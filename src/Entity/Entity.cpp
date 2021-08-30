#include "Entity.hpp"

Billy::Entity::Entity() :
	_texture(),
	_font(),
	_soundBufferPlayerSpawn(),
	_soundBufferGame(),
	_soundSpawnPlayer(),
	_soundGame(),
	_textures(),
	_fonts()
{
	this->_soundBufferPlayerSpawn = new sf::SoundBuffer();
	this->_soundBufferGame = new sf::SoundBuffer();

	this->_soundSpawnPlayer = new sf::Sound();
	this->_soundGame = new sf::Sound();
}

Billy::Entity::~Entity()
{
}

void Billy::Entity::LoadTextureGame(std::string Name, std::string FilePath)
{
	if (Collision::CreateTextureAndBitmask(this->_texture, FilePath))
	{
		this->_textures[Name] = this->_texture;
	}

	this->_texture.setRepeated(this->_texture.isRepeated());

	this->_texture.setSmooth(this->_texture.isSmooth());
}

void Billy::Entity::LoadFontGame(std::string Name, std::string FilePath)
{
	if (this->_font.loadFromFile(FilePath))
	{
		this->_fonts[Name] = this->_font;
	}
}

void Billy::Entity::SoundPlayerSpawn()
{
	if (!this->_soundBufferPlayerSpawn->loadFromFile(PLAYER_SPAWN_SOUND))
	{
		throw(std::runtime_error("Error loading sound").what());
	}

	this->_soundSpawnPlayer->setBuffer(*this->_soundBufferPlayerSpawn);

	this->_soundSpawnPlayer->play();
}

void Billy::Entity::SoundGamePlay()
{
	bool isLoopSoundGame = true;

	if (!this->_soundBufferGame->loadFromFile(SOUND_GAME))
	{
		throw(std::runtime_error("Error loading sound").what());
	}

	this->_soundGame->setBuffer(*this->_soundBufferGame);

	this->_soundGame->setLoop(isLoopSoundGame);

	this->_soundGame->play();
}

sf::Texture& Billy::Entity::GetTextureGame(std::string Name)
{
	return this->_textures.at(Name);
}

sf::Font& Billy::Entity::GetFontGame(std::string Name)
{
	return this->_fonts.at(Name);
}