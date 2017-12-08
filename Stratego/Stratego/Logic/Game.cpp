//
// Created by jeannie on 2017.11.12..
//

#include <map>
#include <iostream>
#include <algorithm>
#include "Game.h"

Game::Game()
    : gameObjects(new GameParts()), validator()
{
    validator.setGameObjects(gameObjects);
}

Game::~Game() {}

void Game::fillStash() {

    std::map<int, int> pieces = {{0, 1}, {1, 1}, {2, 8}, {3, 5}, {4, 4}, {5, 4},
                                 {6, 4}, {7, 3}, {8, 2}, {9, 1}, {10, 1}, {11, 6}};
    for (auto piece : pieces ) {
        int amount = piece.second;
        for (;amount > 0; amount--) {
            gameObjects->createCardInActualStash(piece.first);
        }
    }
}

void Game::initGame() {
    fillStash();
    gameObjects->switchPlayers();
    fillStash();
    gameObjects->switchPlayers();
    gameObjects->hideButtons();
}

void Game::reset() {
    gameObjects->destroyPlayerCards();
    gameObjects->clearPlayerStash();
    fillStash();
}

void Game::step(int index) {
    auto card = gameObjects->getSelected();
    gameObjects->setSelected(-1);

    if (card < 100) {
        gameObjects->boardSwap(index, card);
        return;
    }
    card -= 100;
    gameObjects->moveCardFromStashToBoard(card, index);
}

UserInput::InputType Game::placeCards() {
    auto display = out.lock();
    auto input = in.lock();

    bool quit = false;
    gameObjects->hideReset();
    gameObjects->showOk();
    display->printOut();

    while(!quit) {
        gameObjects->setError(-1);

        switch (input->getUserInput()) {

            case UserInput::SELECT : {
                int index = input->getIndex();
                if (validator.checkPlacement(index)) {
                    step(index);
                    //if (gameObjects->isActualStashEmpty()) { gameObjects->showOk(); }
                    gameObjects->showReset();
                    }
                break;
            }

            case UserInput::QUIT : { return UserInput::QUIT; }

            case UserInput::RESTART : { return UserInput::RESTART; }

            case UserInput::RESET : {
                gameObjects->hideReset();
                reset();
                break;
            }

            case UserInput::OK : {
                if (gameObjects->isActualStashEmpty()) {
                    gameObjects->flipCards();
                    gameObjects->switchPlayers();
                    display->printPause();
                    return UserInput::OK;
                } else {
                    auto first = gameObjects->getPlayerAreaStart();
                    for (auto i=0; i<40; i++) {
                        if (!gameObjects->isCardInBoardAt(first+i)) {
                            gameObjects->setSelected(100);
                            step(first+i);
                        }
                    }
                    gameObjects->showReset();
                }
                break;
            }
        }
        display->printOut();
    }
}

UserInput::InputType Game::battle() {
    auto display = out.lock();
    auto input = in.lock();

    display->printBattle();

    auto to = gameObjects->getTarget();
    auto from = gameObjects->getSelected();

    validator.cancelBattle();

    if (gameObjects->getCardFromBoard(to)->getRank() == 0) {

        auto option = input->getUserInput();
        if (option == UserInput::QUIT) return option;
        display->printWin();

        gameObjects->setTarget(-1);

        bool quit = false;
        while(!quit) {
            switch (input->getUserInput()) {
                case UserInput::QUIT : {
                    return UserInput::QUIT;
                }
                case UserInput::RESTART : {
                    return UserInput::RESTART;
                }
            }
        }
    }

    gameObjects->setSelected(-1);
    gameObjects->setTarget(-1);

    gameObjects->flipCardsDown();
    gameObjects->hideReset();
    gameObjects->hideRestart();
    gameObjects->flipCard(from);
    gameObjects->flipCard(to);

    auto option = input->getUserInput();
    if (option == UserInput::QUIT) return option;
    display->printOut();

    auto defender = &gameObjects->getCardFromBoard(to);
    auto attacker = &gameObjects->getCardFromBoard(from);
    auto result = (*defender)->getBattleResult(*attacker);

    if (result == 'n' || result == 'a') {
        gameObjects->moveCardFromBoardToStash(to);
        if (result == 'a') {
            gameObjects->setSelected(from);
            step(to);
            gameObjects->setSelected(-1);
        }
        option = input->getUserInput();
        if (option == UserInput::QUIT) return option;
        display->printOut();
    }

    gameObjects->switchPlayers();

    if (result == 'd' || result == 'n') {
        gameObjects->moveCardFromBoardToStash(from);
        option = input->getUserInput();
        if (option == UserInput::QUIT) return option;
        display->printOut();
    }

    if (gameObjects->isCardInBoardAt(from)) gameObjects->flipCard(from);
    if (gameObjects->isCardInBoardAt(to)) gameObjects->flipCard(to);

    gameObjects->flipPlayerCardsUp();
    gameObjects->showRestart();

    option = input->getUserInput();
    if (option == UserInput::QUIT) return option;
    display->printPause();

    return UserInput::OK;
}

UserInput::InputType Game::round() {
    auto display = out.lock();
    auto input = in.lock();
    bool quit = false;
    bool stepDone = false;
    int from;
    int to;

    gameObjects->setSelected(-1);
    gameObjects->hideReset();
    display->printOut();

    while(!quit) {
        gameObjects->setError(-1);
        switch (input->getUserInput()) {

            case UserInput::SELECT : {
                if (stepDone) { break; }

                int index = input->getIndex();

                if (validator.checkStep(index)) {
                    from = gameObjects->getSelected();
                    to = index;
                    if (!validator.checkBattle()) { step(index); }
                    stepDone = true;
                    gameObjects->showReset();
                }
                break;
            }

            case UserInput::QUIT : { return UserInput::QUIT; }

            case UserInput::RESTART : { return UserInput::RESTART; }

            case UserInput::RESET : {
                if (!stepDone) { break; }
                if (!validator.checkBattle()) {
                    gameObjects->setSelected(to);
                    step(from);
                } else validator.cancelBattle();
                gameObjects->setTarget(-1);
                gameObjects->hideReset();
                stepDone = false;
                break;
            }

            case UserInput::OK : {
                if (validator.checkBattle()) { return battle(); }
                gameObjects->switchPlayers();
                gameObjects->flipCards();
                display->printPause();
                return UserInput::OK;
            }
        }
        display->printOut();
    }
}

UserInput::InputType Game::start() {

    initGame();

    auto display = out.lock();
    auto input = in.lock();

    display->setResource(gameObjects);
    display->printPause();

    gameObjects->showRestart();

    UserInput::InputType result;

    for (int i = 0; i <2 ; ++i) {
        result = input->getUserInput();
        if (result == UserInput::QUIT) return result;
        result = placeCards();
        if (result != UserInput::OK) return result;
    }

    do {
        result = input->getUserInput();
        if (result == UserInput::QUIT) break;
        result = round();
    } while (result == UserInput::OK);

    return result;
}