//
// Created by jeannie on 2017.11.11..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_TILESET_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_TILESET_HPP

#include <string>
#include <map>

class Tileset {

public:
    Tileset() {}
    virtual ~Tileset() = default;

    std::map<std::string, std::string>themeSet;

    void loadSWTheme() { loadTheme("../Tiles/StarWars/"); }
    void loadBaseTheme() { loadTheme("../Tiles/Base/"); }

private:

    void loadTheme(std::string route) {
        std::string color = "R";
        for (auto player=1; player<3; player++) {
            auto keyp = "P" + std::to_string(player);
            themeSet[keyp+"BG"] = route + color+"BG.png";
            keyp += "R";
            for (auto rank=0; rank<12; rank++) {
                auto key = keyp + std::to_string(rank);
                auto value = route + color + std::to_string(rank) + ".png";
                themeSet[key] = value;
            }
            color = "B";
        }
        themeSet["Splash"] = route + "Splash.jpg";
        themeSet["Board"] = route + "Board.png";
        themeSet["OkBTN"] = route + "OkBTN.png";
        themeSet["ResetBTN"] = route + "ResetBTN.png";
        themeSet["RestartBTN"] = route + "RestartBTN.png";
        themeSet["Pause"] = route + "Waiting.png";
        themeSet["Battle"] = route + "Battle.png";
        themeSet["Win"] = route + "Win.png";
    }
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_TILESET_HPP
