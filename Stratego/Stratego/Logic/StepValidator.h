//
// Created by jeannie on 2017.11.22..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_STEPVALIDATOR_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_STEPVALIDATOR_HPP

#include <memory>
#include "../GameObjects/GameParts.h"

class StepValidator {

public:
    StepValidator() : battle(false) {}
    virtual ~StepValidator() = default;

    void setGameObjects(std::shared_ptr<GameParts>& go) { gameObjects = go; }

    bool isMovableCard(int index);
    bool isInside(int x, int y);
    bool isInTheLake(int index);
    bool hasSpaceToMove(int index);
    bool isValidRange(int from, int to);
    bool isReacheableForAScout(int from, int to);

    bool checkPlacement(int index);
    bool checkStep(int index);
    bool checkBattle() { return battle; };
    void cancelBattle() { battle = false; };

private:
    std::weak_ptr<GameParts> gameObjects;
    bool battle;
};


#endif //CPP_STRATEGO_LOONYLEMMINGS_STEPVALIDATOR_HPP
