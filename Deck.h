#pragma once
#include "Card.h"
#include <vector>

// A standard 52-card deck that can be shuffled and dealt from.
class Deck {
public:
    Deck();                  // Builds and shuffles a full 52-card deck on construction
    Card deal();             // Removes and returns the top card
    int  remaining() const;  // Returns how many cards are left in the deck

    // Returns a read-only view of the remaining cards (used by ProbabilityCalc)
    const std::vector<Card>& cards() const;

private:
    std::vector<Card> m_cards;

    void build();    // Fills m_cards with all 52 cards
    void shuffle();  // Randomly shuffles m_cards using std::shuffle
};
