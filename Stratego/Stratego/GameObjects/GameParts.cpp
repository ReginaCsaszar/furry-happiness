//
// Created by jeannie on 2017.11.12..
//

#include "GameParts.h"

GameParts::GameParts() {

    player1 = std::make_shared<Player>(1);
    player2 = std::make_shared<Player>(2);
    player1->setActive(true);
    player2->setActive(false);
    activePlayer = player1;

    board.reset(new Board());

    p1stash = std::make_shared<card_vector>();
    p2stash = std::make_shared<card_vector>();
    activeStash = p1stash;

    selected = -1;
    wrong = -1;

    buttons["okBtn"] = false;
    buttons["resetBtn"] = false;
    buttons["restartBtn"] = true;
}

//player operations

void GameParts::switchPlayers() {
        player1->setActive(!player1->isActive());
        player2->setActive(!player2->isActive());
        activePlayer = player1->isActive() ? player1 : player2;
        activeStash = player1->isActive() ? p1stash : p2stash;
    }

int GameParts::getPlayerAreaStart() {
        return (activePlayer.lock()->isInMyArea(0)) ? 0 : 60;
    }

bool GameParts::isInPlayerArea(int index) { return activePlayer.lock()->isInMyArea(index); }

player_sptr GameParts::getActualPlayer() { return activePlayer.lock(); }

//stash operations

bool GameParts::isActualStashEmpty() { return activeStash.lock()->empty(); }

int GameParts::getStashSize() { return (int)activeStash.lock()->size(); }

void GameParts::clearPlayerStash() {
        activeStash.lock()->clear();
    }

void GameParts::createCardInActualStash(int piece) {
    auto owner = activePlayer.lock();
    auto stash = activeStash.lock();
    std::unique_ptr<Card> card (new Card(piece, owner));
    stash->push_back(std::move(card));
}

bool GameParts::isCardInStashAt(int index) { return index<activeStash.lock()->size(); }

card_uptr& GameParts::getCardFromStash(int index) { return (*activeStash.lock())[index]; }

//board operations

void GameParts::flipCardsDown() { board->flipAllCardsFaceDown(); }
void GameParts::flipCards() { board->flipAllCards(); }

void GameParts::flipPlayerCardsUp() {
    auto player = activePlayer.lock();
    for (auto i=0; i<100; i++) {
        if (board->getOwnerOf(i)==player) { board->flip(i); }
    }
}

void GameParts::destroyPlayerCards() {
    auto i = getPlayerAreaStart();
    auto end = i+40;
    for (;i<end;i++) { board->deleteCard(i); }
}

void GameParts::flipCard(int index) { board->flip(index); }

bool GameParts::isCardInBoardAt(int index) {
    if (index < 0) return false;
    return board->isCardAt(index);
}

player_sptr GameParts::getOwnerAt(int index) { return board->getOwnerOf(index); }

card_uptr& GameParts::getCardFromBoard(int index) { return board->getCard(index); }

//swaps

void GameParts::boardSwap(int first, int second) { board->swapCards(first, second); }

void GameParts::moveCardFromStashToBoard(int from, int to) {
    auto stash = activeStash.lock();
    board->putCardIn(to, (*stash)[from]);
    stash->erase(stash->begin()+from);
}

void GameParts::moveCardFromBoardToStash(int from) {
    auto stash = activeStash.lock();
    auto card = &board->getCard(from);
    stash->push_back(std::move(*card));
    board->deleteCard(from);
}