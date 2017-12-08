//
// Created by jeannie on 2017.11.15..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_GO_CONTAINER_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_GO_CONTAINER_HPP

#include "DPBase.hpp"
#include "DPField.hpp"

class DPContainer : public DPBase {

public:
    DPContainer(int sx, int sy, int rw, int cl, const DPField fld)
        : DPBase(sx, sy), row(rw), col(cl),
          cell(DPField(fld.cellW, fld.cellH, fld.gap))
    {
        endX = startX + cell.cellW*row;
        endY = startY + cell.cellH*col;
    }

    virtual ~DPContainer() {}

    bool isInside(DPBase& index) const override {
        return index.startX>startX && index.startY>startY
               && index.startX<endX && index.startY<endY;
    }

    DPBase getCoords(int index) const {
        int x = index%row;
        int y = (index-x)/row;
        return DPBase(x*cell.cardW + startX + cell.gap*x,
                       y*cell.cardH + startY + cell.gap*y);
    }

    int getIndex(DPBase& field) const {
        return (field.startY-startY)/(cell.cellH) * row
               + (field.startX-startX)/(cell.cellW);
    }

    int endX;
    int endY;
    int row;
    int col;

private:
    DPField cell;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_GO_CONTAINER_HPP
