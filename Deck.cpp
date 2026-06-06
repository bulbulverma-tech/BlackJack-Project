#include "Deck.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck()
{
    build();
    shuffle();
}

// Constructs all 52 cards: 4 suits × 13 ranks.
// Face cards (J, Q, K) are worth 10; Aces start at 11 (Hand reduces them if needed).
void Deck::build()
{
    const std::vector<std::string> suits = {"Spades", "Hearts", "Diamonds", "Clubs"};
    const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const std::vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    m_cards.clear();
    for (const auto &suit : suits)
    {
        for (size_t i = 0; i < ranks.size(); ++i)
        {
            m_cards.push_back({ranks[i], suit, values[i]});
        }
    }
}

// Uses a Mersenne Twister seeded from hardware entropy for a proper random shuffle.
void Deck::shuffle()
{
    std::mt19937 rng(std::random_device{}());
    std::shuffle(m_cards.begin(), m_cards.end(), rng);
}

// Takes the top card off the deck and returns it.
Card Deck::deal()
{
    if (m_cards.empty())
    {
        throw std::runtime_error("Deck is empty; cannot deal.");
    }
    Card top = m_cards.back();
    m_cards.pop_back();
    return top;
}

int Deck::remaining() const
{
    return static_cast<int>(m_cards.size());
}

const std::vector<Card> &Deck::cards() const
{
    return m_cards;
}
