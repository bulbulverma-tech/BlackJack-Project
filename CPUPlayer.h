#pragma once
#include "Hand.h"
#include "Deck.h"

// Difficulty levels that control how smart the CPU opponent is.
enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

// The CPU player uses its difficulty level to decide whether to hit or stand.
// Easy  - random coin-flip decision (ignores all math).
// Medium - hits if score < 17 (mirrors basic dealer rules).
// Hard   - hits only if ProbabilityCalc reports < 40% bust chance.
class CPUPlayer
{
public:
    explicit CPUPlayer(Difficulty diff = Difficulty::Medium);

    // Returns true if the CPU decides to hit (draw another card).
    bool shouldHit(const Hand &hand, const Deck &deck) const;

    std::string difficultyName() const;

private:
    Difficulty m_difficulty;
};
