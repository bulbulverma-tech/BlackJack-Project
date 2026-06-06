#pragma once
#include "Deck.h"

// Calculates real-time odds based on the cards still remaining in the deck.
// This is the core HD feature - it applies combinatorics from Discrete Mathematics:
//   P(bust on next card) = (count of cards that would push score over 21) / (total cards remaining)
class ProbabilityCalc
{
public:
    // Returns the probability (0.0–1.0) that drawing one card from the given deck
    // would cause a hand with the given current score to bust (exceed 21).
    static double bustChance(int currentScore, const Deck &deck);

    // Returns a user-friendly percentage string, e.g. "Hit risk: 38% bust chance"
    static std::string bustMessage(int currentScore, const Deck &deck);
};
