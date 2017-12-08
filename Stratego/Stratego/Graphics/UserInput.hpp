//
// Created by jeannie on 2017.11.11..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_INPUT_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_INPUT_HPP

class UserInput {

public:
    enum InputType {QUIT, OK, RESTART, SELECT, RESET, NOTHING};

    UserInput() = default;
    virtual ~UserInput() = default;
    virtual InputType getUserInput() = 0;
    virtual int getIndex() = 0;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_INPUT_HPP
