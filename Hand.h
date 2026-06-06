#pragma once
#include "Card.h"
#include <vector>
#include <string>

// Represents one player's hand of cards for a single round.
class Hand {
public:
    void addCard(const Card& card);  // Adds a card and recalculates the score

    int  score()   const;  // Current best score (aces auto-adjust to avoid bust)
    bool isBust()  const;  // True if score > 21
    bool isBlackjack() const;  // True if exactly 2 cards totalling 21

    // Prints each card in the hand as a space-separated row, e.g. [A♠] [7♣]
    void display(bool hideFirst = false) const;

    int  size() const;  // Number of cards held

private:
    std::vector<Card> m_cards;
    int m_score = 0;
    int m_aces  = 0;  // Tracks how many aces are currently counted as 11

    void recalculate();  // Recomputes m_score, reducing aces from 11→1 as needed
};
