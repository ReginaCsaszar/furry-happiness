//
// Created by jeannie on 2017.11.12..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_GAME_H
#define CPP_STRATEGO_LOONYLEMMINGS_GAME_H

#include "../Graphics/Display.hpp"
#include "../Graphics/UserInput.hpp"
#include "StepValidator.h"

class Game {

public:
    Game();
    virtual ~Game();

    void setDisplay(std::shared_ptr<Display>& screen) { out = screen; }
    void setInput(std::shared_ptr<UserInput>& user) { in = user; }

    UserInput::InputType start();

private:
    std::weak_ptr<Display> out;
    std::weak_ptr<UserInput> in;

    std::shared_ptr<GameParts> gameObjects;
    StepValidator validator;

    void fillStash();
    void initGame();
    void reset();
    void step(int index);

    UserInput::InputType placeCards();
    UserInput::InputType battle();
    UserInput::InputType round();

};


#endif //CPP_STRATEGO_LOONYLEMMINGS_GAME_H
