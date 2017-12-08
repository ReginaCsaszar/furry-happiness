//
// Created by jeannie on 2017.11.11..
//

#include <iostream>
#include "MouseInput.h"

MouseInput::InputType MouseInput::getUserInput() {
    bool quit = false;
    index = -1;
    SDL_Event e;

    while(!quit) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                DPBase click(0, 0);
                SDL_GetMouseState(&click.startX, &click.startY);
                switch (gOutput.getPart(click)) {
                    case DisplayParts::DisplayPart::BOARD : {
                        index = gOutput.board.getIndex(click);
                        return SELECT;
                    }
                    case DisplayParts::DisplayPart::STASH : {
                        index = gOutput.stash.getIndex(click)+100;
                        return SELECT;
                    }
                    case DisplayParts::DisplayPart::OK : {
                        return OK;
                    }
                    case DisplayParts::DisplayPart::RESET : {
                        return RESET;
                    }
                    case DisplayParts::DisplayPart::RESTART : {
                        return RESTART;
                    }
                    default: {
                        return NOTHING;
                    }
                }
            }

            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
    }
    return QUIT;
}