#include "Hand.h"
#include <iostream>

void Hand::addCard(const Card& card) {
    m_cards.push_back(card);
    if (card.rank == "A") ++m_aces;
    recalculate();
}

// Sums card values, then reduces aces from 11 to 1 one at a time
// until the score is 21 or under (or no aces remain to reduce).
void Hand::recalculate() {
    m_score = 0;
    for (const auto& c : m_cards) m_score += c.value;

    // Each reduction turns one ace from 11 into 1 (a difference of 10)
    int acesAsEleven = m_aces;
    while (m_score > 21 && acesAsEleven > 0) {
        m_score    -= 10;
        --acesAsEleven;
    }
}

int  Hand::score()       const { return m_score; }
bool Hand::isBust()      const { return m_score > 21; }
bool Hand::isBlackjack() const { return m_cards.size() == 2 && m_score == 21; }
int  Hand::size()        const { return static_cast<int>(m_cards.size()); }

// Prints the hand to stdout.
// If hideFirst is true (used for the dealer's initial reveal), the first card
// is printed as [??] so the player cannot see it.
void Hand::display(bool hideFirst) const {
    for (size_t i = 0; i < m_cards.size(); ++i) {
        if (i == 0 && hideFirst)
            std::cout << "[??] ";
        else
            std::cout << m_cards[i].display() << " ";
    }
    std::cout << std::endl;
}
