#include "Card.h"

// Maps suit names to their Unicode suit symbols for a nicer terminal display
static std::string suitSymbol(const std::string &suit)
{
    if (suit == "Spades")
        return "S";
    if (suit == "Hearts")
        return "H";
    if (suit == "Diamonds")
        return "D";
    if (suit == "Clubs")
        return "C";
    return "?";
}

std::string Card::display() const
{
    return "[" + rank + " of " + suit + "]";
}
