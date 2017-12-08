//
// Created by jeannie on 2017.11.15..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_GO_ELEM_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_GO_ELEM_HPP

#include "DPBase.hpp"

class DPElem : public DPBase {

public:
    DPElem(int sx, int sy, int wdt, int hgt)
            : DPBase(sx, sy)
    {
        width = wdt;
        height = hgt;
        endX = sx+wdt;
        endY = sy+hgt;
    }

    virtual ~DPElem() {}

    SDL_Rect getRect() const {
        return {startX, startY, width, height};
    }

    bool isInside(DPBase& index) const override {
        return index.startX>startX && index.startY>startY
               && index.startX<endX && index.startY<endY;
    }

    int width;
    int height;
    int endX;
    int endY;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_GO_ELEM_HPP
