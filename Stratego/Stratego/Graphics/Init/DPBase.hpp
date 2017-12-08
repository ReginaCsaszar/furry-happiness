//
// Created by jeannie on 2017.11.15..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_GO_BOARD_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_GO_BOARD_HPP

#include <SDL_rect.h>

class DPBase {

public:
    DPBase(int x, int y)
        : startX(x), startY(y) {}

    virtual ~DPBase() {}

	virtual bool isInside(DPBase& index) const {
		return (index.startX == startX && index.startY == startY); 
	}

    int startX;
    int startY;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_GO_BOARD_HPP
