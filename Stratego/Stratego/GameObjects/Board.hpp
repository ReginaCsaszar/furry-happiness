//
// Created by jeannie on 2017.11.25..
//

#ifndef CPP_STRATEGO_LOONYLEMMINGS_BOARD_HPP
#define CPP_STRATEGO_LOONYLEMMINGS_BOARD_HPP

#include "Card.hpp"
#include <array>

using cuptr = std::unique_ptr<Card>;
using psptr = std::shared_ptr<Player>;

class Board {

public:
    Board() {
        for (auto i = 0; i<100; i++) {
            board[i].reset();
        }
    }

    void flipAllCardsFaceDown() {
        for (auto i=0; i<100; i++) {
            if (board[i] && board[i]->isFaceUp()) {
                flip(i);
            }
        }
    }

    void flipAllCards() {
        for (auto i=0; i<100; i++) {
            if (board[i]) flip(i);
        }
    }

    void flip(int index) { board[index]->flip(); }

    bool isCardAt(int index) { return board[index]!= nullptr;}

    psptr getOwnerOf(int index) {
        if (isCardAt(index)) return board[index]->getOwner();
        return nullptr;
    }
    cuptr& getCard(int index) { return board[index]; }

    void deleteCard(int index) {
        if (isCardAt(index)) board[index].reset();
    }
    void swapCards(int first, int second) {
        board[first].swap(board[second]);
    }
    void putCardIn(int index, cuptr& card) {
        board[index] = std::move(card);
    }

private:
    std::array<cuptr, 100> board;
};

#endif //CPP_STRATEGO_LOONYLEMMINGS_BOARD_HPP
