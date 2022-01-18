#include "./Game/Game.hpp"

int main(void)
{
	Billy::Game* ReduxAdventure = new Billy::Game(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

	ReduxAdventure->RunGame();

	return EXIT_SUCCESS;
}
