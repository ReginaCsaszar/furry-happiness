#include "Graphics/GrapicalOutput.h"
#include "Graphics/Display.hpp"
#include "Graphics/UserInput.hpp"
#include "Graphics/MouseInput.h"
#include "Logic/Game.h"

int main(int argc, char* args[]) {

	std::shared_ptr<Display> display(new GrapicalOutput());
	std::shared_ptr<UserInput> input(new MouseInput());

	bool quit;

	do {
		Game game;

		game.setDisplay(display);
		game.setInput(input);

		quit = game.start() == UserInput::QUIT;

	} while (!quit);

	display->close();
	return 0;
}