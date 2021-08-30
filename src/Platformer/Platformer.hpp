#pragma once

#ifndef PLATFORMER_HPP
	#define PLATFORMER_HPP

	#include <SFML/Graphics.hpp>

	#include <vector>
	#include <array>
	#include <string>

	#include "./Entity/Entity.hpp"
	#include "./Game/Game.hpp"

class Entity;

namespace Billy
{
class Platformer
{
public:
	Platformer();
	virtual ~Platformer();

public:
	void LoadPlatformerGame();
	void FPSGame();
	void GetFPSGame(float FrameRate);
	void ScoreGame();
	void BestScoreGame();
	void GetScoreGame(int ScoreGame);
	void GetBestScoreGame(int BestScoreGame);

	virtual void DrawPlatformer(sf::RenderWindow& Window) const;

public:
	const sf::Sprite& GroundSprite() const;
	const sf::Sprite& RocksTreesSprite() const;

	const sf::FloatRect GetGroundBounds() const;
	const sf::FloatRect GetRocksTreesBounds() const;

private:
	Entity* Entity_Object;

private:
	sf::Sprite _layerSkySprite;
	sf::Sprite _layerCastleSprite;
	sf::Sprite _layerTreesSprite;
	sf::Sprite _layerGroundSprite;
	sf::Sprite _layerCloudsSprite;
	sf::Sprite _layerHillsSprite;
	sf::Sprite _layerRocksSprite;

	sf::Text _scoreGameText;
	sf::Text _bestScoreGameText;
	sf::Text _fpsGameText;

private:
	std::vector<sf::Sprite> _layerSkyVec;
	std::vector<sf::Sprite> _layerGroundVec;
	std::vector<sf::Sprite> _layerCastleVec;
	std::vector<sf::Sprite> _layerTreesVec;
	std::vector<sf::Sprite> _layerCloudsVec;
	std::vector<sf::Sprite> _layerHillsVec;
	std::vector<sf::Sprite> _layerRocksVec;

protected:
	float _frameRate;

	int _scoreGame;
	int _bestScoreGame;
};
}

#endif // PLATFORMER_HPP