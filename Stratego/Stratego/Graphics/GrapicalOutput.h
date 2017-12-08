//
// Created by jeannie on 2017.11.11..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_GRAPICALOUTPUT_H
#define CPP_STRATEGO_LOONYLEMMINGS_GRAPICALOUTPUT_H

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <map>

#include "Display.hpp"
#include "Init/DisplayParts.hpp"
#include "Init/Tileset.hpp"

class GrapicalOutput : public Display {

public:
    GrapicalOutput();

    void setResource(std::shared_ptr<GameParts>& parts) override;
    void printOut() override;
    void printPause() override;
    void printBattle() override;
    void printWin() override;
    void close() override;

private:

    struct sdl_deleter
    {
        void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
        void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
        void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    };

    std::unique_ptr<SDL_Window, sdl_deleter> gWindow = nullptr;
    std::unique_ptr<SDL_Renderer, sdl_deleter> gRenderer = nullptr;

    const DisplayParts dParts;

    std::map< std::string, std::unique_ptr<SDL_Texture, sdl_deleter> > pictures;

    bool init();
    bool loadMedia();
    void drawBoard();
    void drawSelection();
    void drawFrame(int index);
    void drawButtons();
    void drawBtn(std::string name, DPElem button);

    void printInfo();
};


#endif //CPP_STRATEGO_LOONYLEMMINGS_GRAPICALOUTPUT_H
