//
// Created by jeannie on 2017.11.11..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_PLAYER_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_PLAYER_HPP

#include <string>

class Player {

public:
    Player() = delete;

    explicit Player(int number)
        : id(number), active(false)
    {
    shortName = 'P' + std::to_string(id);
    firstTile = (id == 1) ? 0 : 60;
    lastTile = firstTile + 39;
    }

    int getId() const { return id; }

    bool isActive() { return active; }

    const std::string &getShortName() const { return shortName; }

    bool isInMyArea(int index) { return index<=lastTile&&index>=firstTile; }

    void setActive(bool state) { active = state; }

    virtual ~Player() = default;

private:
    int id;
    int firstTile;
    int lastTile;
    bool active;
    std::string shortName;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_PLAYER_HPP
