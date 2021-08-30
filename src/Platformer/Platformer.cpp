#include "Platformer.hpp"

#include <algorithm>

static constexpr auto SCORE_CHARACTER_SIZE = 30.5f;
static constexpr auto BEST_SCORE_CHARACTER_SIZE = 30.0f;
static constexpr auto FPS_CHARACTER_SIZE = 20.0f;

Billy::Platformer::Platformer() :
	Entity_Object(),
	_layerSkySprite(),
	_layerCastleSprite(),
	_layerTreesSprite(),
	_layerGroundSprite(),
	_layerCloudsSprite(),
	_layerHillsSprite(),
	_layerRocksSprite(),
	_scoreGameText(),
	_fpsGameText(),
	_layerSkyVec(),
	_layerGroundVec(),
	_layerCastleVec(),
	_layerTreesVec(),
	_layerCloudsVec(),
	_layerHillsVec(),
	_layerRocksVec(),
	_scoreGame()
{
	// Constructor class
	this->Entity_Object = new Entity();

	// Score game
	this->_scoreGame = 0;
	this->_bestScoreGame = this->_scoreGame;
}

Billy::Platformer::~Platformer()
{
}

void Billy::Platformer::LoadPlatformerGame()
{
	// Set layers sprite
	const std::array<std::string, 10> name = { "Layer Ground", "Layer Trees", "Layer Castle", "Layer Clouds", "Layer Hills", "Layer Rocks", "Layer Sky" };

	// Layer ground
	static float scaleVectorX = 0.8f;
	static float scaleVectorY = 0.7f;

	this->Entity_Object->LoadTextureGame(name[0], LAYER_GROUND);

	this->_layerGroundSprite.setTexture(this->Entity_Object->GetTextureGame(name[0]));
	this->_layerGroundSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerGroundVec.push_back(sf::Sprite(this->_layerGroundSprite));

	// Layer trees
	this->Entity_Object->LoadTextureGame(name[1], LAYER_TREES);

	this->_layerTreesSprite.setTexture(this->Entity_Object->GetTextureGame(name[1]));
	this->_layerTreesSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerTreesVec.push_back(sf::Sprite(this->_layerTreesSprite));

	// Layer castle
	this->Entity_Object->LoadTextureGame(name[2], LAYER_CASTLE);

	this->_layerCastleSprite.setTexture(this->Entity_Object->GetTextureGame(name[2]));
	this->_layerCastleSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerCastleVec.push_back(sf::Sprite(this->_layerCastleSprite));

	// Layer clouds
	this->Entity_Object->LoadTextureGame(name[3], LAYER_CLOUDS);

	this->_layerCloudsSprite.setTexture(this->Entity_Object->GetTextureGame(name[3]));
	this->_layerCloudsSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerCloudsVec.push_back(sf::Sprite(this->_layerCloudsSprite));

	// Layer hills
	this->Entity_Object->LoadTextureGame(name[4], LAYER_HILLS);

	this->_layerHillsSprite.setTexture(this->Entity_Object->GetTextureGame(name[4]));
	this->_layerHillsSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerHillsVec.push_back(sf::Sprite(this->_layerHillsSprite));

	// Layer rocks
	this->Entity_Object->LoadTextureGame(name[5], LAYER_ROCKS);

	this->_layerRocksSprite.setTexture(this->Entity_Object->GetTextureGame(name[5]));
	this->_layerRocksSprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerRocksVec.push_back(sf::Sprite(this->_layerRocksSprite));

	// Layer sky
	this->Entity_Object->LoadTextureGame(name[6], LAYER_SKY);

	this->_layerSkySprite.setTexture(this->Entity_Object->GetTextureGame(name[6]));
	this->_layerSkySprite.setScale(sf::Vector2f({ scaleVectorX, scaleVectorY }));

	this->_layerSkyVec.push_back(sf::Sprite(this->_layerSkySprite));

	// FPS game
	this->FPSGame();

	// Score game
	this->ScoreGame();

	this->BestScoreGame();
}

void Billy::Platformer::FPSGame()
{
	const std::array<std::string, 5> name = { "FPS Game" };

	this->Entity_Object->LoadFontGame(name[0], FONT_GAME);

	static float positionX = 1288.0f; // 1295.0f if using setView

	static float positionY = 0.0f;

	this->_fpsGameText.setFont(this->Entity_Object->GetFontGame(name[0]));
	this->_fpsGameText.setOutlineThickness(3.5f);
	this->_fpsGameText.setOutlineColor(sf::Color({ 32, 32, 32 }));
	this->_fpsGameText.setPosition(sf::Vector2f({ positionX, positionY }));

	this->GetFPSGame(this->_frameRate);

	this->_fpsGameText.setCharacterSize(FPS_CHARACTER_SIZE);
}

void Billy::Platformer::ScoreGame()
{
	const std::array<std::string, 5> name = { "Score Game" };

	this->Entity_Object->LoadFontGame(name[0], FONT_GAME);

	this->_scoreGameText.setFont(this->Entity_Object->GetFontGame(name[0]));
	this->_scoreGameText.setPosition(sf::Vector2f({ 8.0f, 0.0f }));
	this->_scoreGameText.setOutlineThickness(3.5f);
	this->_scoreGameText.setOutlineColor(sf::Color({ 32, 32, 32 }));

	this->GetScoreGame(this->_scoreGame);

	this->_scoreGameText.setCharacterSize(SCORE_CHARACTER_SIZE);
}

void Billy::Platformer::BestScoreGame()
{
	const std::array<std::string, 5> name = { "Best Score Game" };

	this->Entity_Object->LoadFontGame(name[0], FONT_GAME);

	this->_bestScoreGameText.setFont(this->Entity_Object->GetFontGame(name[0]));
	this->_bestScoreGameText.setPosition(sf::Vector2f({ 8.0f, 35.0f }));
	this->_bestScoreGameText.setOutlineThickness(3.5f);
	this->_bestScoreGameText.setOutlineColor(sf::Color({ 32, 32, 32 }));

	this->GetBestScoreGame(this->_bestScoreGame);

	this->_bestScoreGameText.setCharacterSize(BEST_SCORE_CHARACTER_SIZE);
}

void Billy::Platformer::GetFPSGame(float FrameRate)
{
	std::size_t indexPos = 0;

	std::size_t charSubString = 2;

	this->_fpsGameText.setString("FPS: " + std::to_string(std::floor(FrameRate)).substr(indexPos, charSubString)); // Remove floating numbers
}

void Billy::Platformer::GetScoreGame(int ScoreGame)
{
	static std::string score = "Score: ";

	this->_scoreGameText.setString(score + std::to_string(ScoreGame));
}

void Billy::Platformer::GetBestScoreGame(int BestScoreGame)
{
	static std::string bestScore = "Best: ";

	this->_bestScoreGameText.setString(bestScore + std::to_string(BestScoreGame));
}

const sf::Sprite& Billy::Platformer::GroundSprite() const
{
	return this->_layerGroundSprite;
}

const sf::Sprite& Billy::Platformer::RocksTreesSprite() const
{
	return this->_layerRocksSprite;
}

const sf::FloatRect Billy::Platformer::GetGroundBounds() const
{
	return this->_layerGroundSprite.getGlobalBounds();
}

const sf::FloatRect Billy::Platformer::GetRocksTreesBounds() const
{
	return this->_layerRocksSprite.getGlobalBounds();
}

void Billy::Platformer::DrawPlatformer(sf::RenderWindow& Window) const
{
	// Draw background layers
	for (const auto& sky : this->_layerSkyVec)
	{
		Window.draw(sky);
	}

	for (const auto& rocks : this->_layerRocksVec)
	{
		Window.draw(rocks);
	}

	for (const auto& clouds : this->_layerCloudsVec)
	{
		Window.draw(clouds);
	}

	for (auto hills = this->_layerHillsVec.begin(); hills != this->_layerHillsVec.end(); ++hills)
	{
		Window.draw(*hills);
	}

	for (auto castle = this->_layerCastleVec.begin(); castle != this->_layerCastleVec.end(); ++castle)
	{
		Window.draw(*castle);
	}

	for (auto trees = this->_layerTreesVec.begin(); trees != this->_layerTreesVec.end(); ++trees)
	{
		Window.draw(*trees);
	}

	for (auto ground = this->_layerGroundVec.begin(); ground != this->_layerGroundVec.end(); ++ground)
	{
		Window.draw(*ground);
	}

	// Draw FPS game
	Window.draw(this->_fpsGameText);

	// Draw score game
	Window.draw(this->_scoreGameText);

	Window.draw(this->_bestScoreGameText);
}