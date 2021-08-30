#pragma once

#ifndef Entity_HPP
	#define Entity_HPP

	#include <SFML/Graphics.hpp>
	#include <SFML/Graphics/Texture.hpp>
	#include <SFML/Graphics/Sprite.hpp>
	#include <SFML/Graphics/Font.hpp>
	#include <SFML/Graphics/Text.hpp>
	#include <SFML/Graphics/RenderTarget.hpp>
	#include <SFML/Graphics/RenderStates.hpp>
	#include <SFML/Window/Window.hpp>
	#include <SFML/System/Clock.hpp>
	#include <SFML/System/Time.hpp>
	#include <SFML/Audio.hpp>

	#include <vector>
	#include <map>
	#include <memory>

	#include "DefinitionsGame.hpp"

	#include "Collision/Collision.h"

namespace Billy
{
class Entity
{
public:
	Entity();
	virtual ~Entity();

public:
	virtual void LoadTextureGame(std::string Name, std::string FilePath);
	virtual void LoadFontGame(std::string Name, std::string FilePath);

	virtual void SoundPlayerSpawn();
	virtual void SoundGamePlay();

public:
	sf::Texture& GetTextureGame(std::string Name);
	sf::Font& GetFontGame(std::string Name);

private:
	sf::Texture _texture;
	sf::Font _font;

	sf::SoundBuffer* _soundBufferPlayerSpawn;
	sf::SoundBuffer* _soundBufferGame;

	sf::Sound* _soundSpawnPlayer;
	sf::Sound* _soundGame;

private:
	std::unordered_map<std::string, sf::Texture> _textures;
	std::unordered_map<std::string, sf::Font> _fonts;
};
}

#endif // Entity_HPP