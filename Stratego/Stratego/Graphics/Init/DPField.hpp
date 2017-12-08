//
// Created by jeannie on 2017.11.15..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_FIELD_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_FIELD_HPP

#include "DPBase.hpp"

class DPField : public DPBase {

public:
    DPField(int width, int height, int gap)
            : DPBase(0, 0), gap(gap), cellW(width), cellH(height)
    {
        cardH = cellH-2;
        cardW = cellW-2;
    }

    virtual ~DPField() {}

    SDL_Rect getRect(DPBase &content) const {
        return {content.startX, content.startY, cardW, cardH};
    }

    void setInnerRect(SDL_Rect &sel) const {
        sel.x++; sel.y++; sel.w -= 2; sel.h -= 2;
    }

    SDL_Rect getRectForBattleInfoAttacker() const {
        return {415, 300, cardW, cardH};
    }

    void setRectForBattleInfoDefender(SDL_Rect &sel) const {
        sel.x += cardW + 15;
    }

    SDL_Rect getRectForFlag() const {
        return {450, 345, cardW, cardH};
    }

    const int gap;
    const int cellW;
    const int cellH;
    int cardW;
    int cardH;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_FIELD_HPP
