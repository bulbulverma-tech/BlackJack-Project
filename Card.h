#pragma once
#include <string>

// Represents a single playing card with a suit, rank, and point value.
struct Card {
    std::string rank;   // e.g. "A", "K", "7"
    std::string suit;   // e.g. "Spades", "Hearts"
    int         value;  // Numeric value (Ace = 11 by default; Hand adjusts it down if needed)

    // Returns a short display string, e.g. "[A♠]"
    std::string display() const;
};
