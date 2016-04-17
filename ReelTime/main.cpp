#include "game_state.h"
#include "intro_menu.h"
#include "config.h"
#include "game_speed.h"

game_state coreState;
bool quitGame = false;

int main()
{
	//reset random
	srand(time(NULL));



	//init window
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	sf::RenderWindow window(sf::VideoMode(Config::screen_width, Config::screen_height), "Reel Time", sf::Style::Resize, antialiasing);


	//init game speed
	game_speed gameSpeed;
	gameSpeed.Initialize(&window);


	//set data to coreState
	coreState.SetWindow(&window);
	coreState.SetGameSpeed(&gameSpeed);
	coreState.SetState(new intro_menu());


	sf::Clock deltaTime; float dt = 0.001;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		coreState.Update(dt);
		coreState.Render(dt);

		dt = deltaTime.restart().asSeconds();

		window.display();

		if (quitGame)
		{
			window.close();
		}
	}

	return 0;
}
