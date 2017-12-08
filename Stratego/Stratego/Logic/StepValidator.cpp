//
// Created by jeannie on 2017.11.22..
//

#include <iostream>
#include "StepValidator.h"

bool StepValidator::checkPlacement(int index) {

    auto game = gameObjects.lock();

    if (index>99 && game->isCardInStashAt(index-100)) {
        game->setSelected(index);
        return false;
    }

    if (game->isInPlayerArea(index)) {
        if (game->getCardFromBoard(index)) {
            game->setSelected(index);
            return false;
        }
        if (game->getSelected() >= 0) {
            return true;
        }
    }
    game->setError(index);
    return false;
}

bool StepValidator::isInside(int x, int y) {
    return (x >= 0)&&(x < 10)&&(y >= 0)&&(y<10);
}

bool StepValidator::isMovableCard(int index) {
    auto game = gameObjects.lock();
    return game->getCardFromBoard(index)->getMaxMove() != 0;
}

bool StepValidator::hasSpaceToMove(int index) {
    auto game = gameObjects.lock();
    auto player = game->getActualPlayer();

    int ox = index%10;
    int oy = (index >= 10) ? (index-ox)/10 : 0;
    int y = oy-1;
    int x = ox;

    for (int i = 0; i < 4; ++i) {
        auto check = y*10+x;
        if (isInside(x, y) && !isInTheLake(check)) {
            if (!game->isCardInBoardAt(check)) { return true; }
            if (game->getOwnerAt(check) != player) { return true; }
        }
        y = (x == ox-1) ? oy : y+1;
        x = (x == ox) ? x-1 : (y == oy) ? ox+1 : ox;
    }
    return false;
}

bool StepValidator::isInTheLake(int index) {
    return index == 42 || index == 43 || index == 52 || index == 53
            || index == 46 || index == 47 || index == 56 || index == 57;
}

bool StepValidator::isValidRange(int from, int to) {
    if (isInTheLake(to)) return false;
    auto dist = from-to;

    return dist == 1 || dist == 10 || dist == -1 || dist == -10;
}

bool StepValidator::isReacheableForAScout(int from, int to) {
    if (isInTheLake(to)) return false;

    int sx = from%10;
    int sy = (from>=10) ? (from-sx)/10 : 0;
    int ex = to%10;
    int ey = (to>=10) ? (to-ex)/10 : 0;

    int step = (sx == ex) ? 10 : (sy == ey) ? 1 : 0;
    if (step == 0) return false;

    auto game = gameObjects.lock();
    if (from>to) { step = 0-step; }

    for (auto i = from+step; i != to; i += step) {
        if (isInTheLake(i)) return false;
        if (game->isCardInBoardAt(i)) return false;
    }
    return true;
}

bool StepValidator::checkStep(int index) {
    battle = false;
    auto game = gameObjects.lock();

    if (index>99) {
        game->setError(index);
        return false;
    }

    auto owner = game->getOwnerAt(index);
    auto player = game->getActualPlayer();

    if (owner == player) {
        if (hasSpaceToMove(index) && isMovableCard(index)) {
            game->setSelected(index);
            return false;
        }
        game->setError(index);
        return false;
    }

    auto selected = game->getSelected();

    if (selected < 0) {
        game->setError(index);
        return false;
    }

    if (isValidRange(selected, index)) {
        if (owner) {
            battle = true;
            game->setTarget(index);
        }
        return true;
    }

    if (game->getCardFromBoard(selected)->getMaxMove() == 10
        && isReacheableForAScout(selected, index)) {
        if (owner) {
            battle = true;
            game->setTarget(index);
        }
        return true;
    }

    game->setError(index);
    return false;
}