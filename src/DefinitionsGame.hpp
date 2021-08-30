#pragma once

#ifndef DEFINITIONS_GAME_HPP
	#define DEFINITIONS_GAME_HPP

// Window screen size and game title
static constexpr auto SCREEN_WIDTH = 1375.f;
static constexpr auto SCREEN_HEIGHT = 680.f;
static constexpr auto GAME_TITLE = "Redux Adventure";

// Font game
constexpr auto FONT_GAME = "Assets/Fonts/cocogoose.ttf";

// Layers background gameplay
constexpr auto LAYER_GROUND = "Assets/Backgrounds/platformer_background_4/Layers/layer01_Ground.png";
constexpr auto LAYER_TREES = "Assets/Backgrounds/platformer_background_4/Layers/layer02_Trees_rocks.png";
constexpr auto LAYER_CASTLE = "Assets/Backgrounds/platformer_background_4/Layers/layer03_Hills_Castle.png";
constexpr auto LAYER_CLOUDS = "Assets/Backgrounds/platformer_background_4/Layers/layer04_Clouds.png";
constexpr auto LAYER_HILLS = "Assets/Backgrounds/platformer_background_4/Layers/layer05_Hills.png";
constexpr auto LAYER_ROCKS = "Assets/Backgrounds/platformer_background_4/Layers/layer06_Rocks.png";
constexpr auto LAYER_SKY = "Assets/Backgrounds/platformer_background_4/Layers/layer07_Sky.png";

constexpr auto BACKGROUND = "Assets/Backgrounds/platformer_background_4/platformer_background_4.png";

// Player character
constexpr auto MALE_CHARACTER_SHEET = "Assets/Characters/MaleAdventure/Tilesheet/character_maleAdventurer_sheetHD.png";

// Zombie enemy character
constexpr auto ZOMBIE_ENEMY_SHEET = "Assets/Characters/Zombie/Tilesheet/character_zombie_sheetHD.png";

// Robot enemy character
constexpr auto ROBOT_ENEMY_SHEET = "Assets/Characters/Robot/Tilesheet/character_robot_sheetHD.png";

// Male enemy character
constexpr auto MALE_ENEMY_SHEET = "Assets/Characters/MalePerson/Tilesheet/character_malePerson_sheetHD.png";

	// Music and sound effect game
	#define SOUND_GAME ("Assets/Sound/Game.wav")
	#define PLAYER_SPAWN_SOUND ("Assets/Sound/Spawn.ogg")
	#define PLAYER_JUMP_SOUND ("Assets/Sound/jump.wav")
	#define PLAYER_FALL_SOUND ("Assets/Sound/fall.wav")
	#define PLAYER_HIT_SOUND ("Assets/Sound/hit.wav")

#endif // DEFINITIONS_GAME_HPP