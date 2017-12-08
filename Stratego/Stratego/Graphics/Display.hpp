//
// Created by jeannie on 2017.11.11..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_OUTPUT_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_OUTPUT_HPP

#include <memory>
#include "../GameObjects/GameParts.h"

class Display {

public:
    Display() = default;
    virtual ~Display() = default;

    virtual void printOut() = 0;
    virtual void printPause() = 0;
    virtual void printBattle() = 0;
    virtual void printWin() = 0;

    virtual void setResource(std::shared_ptr<GameParts>& parts) = 0;
    virtual void close() = 0;

protected:
    std::weak_ptr<GameParts> game;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_OUTPUT_HPP
