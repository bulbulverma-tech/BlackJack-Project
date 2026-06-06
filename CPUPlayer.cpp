#include "CPUPlayer.h"
#include "ProbabilityCalc.h"
#include <cstdlib>

CPUPlayer::CPUPlayer(Difficulty diff) : m_difficulty(diff) {}

bool CPUPlayer::shouldHit(const Hand &hand, const Deck &deck) const
{
    int score = hand.score();

    // Never hit on 21 - no point regardless of difficulty
    if (score == 21)
        return false;

    switch (m_difficulty)
    {

    case Difficulty::Easy:
        // Random: 50/50 coin flip. Demonstrates that skill matters!
        return (std::rand() % 2 == 0);

    case Difficulty::Medium:
        // Basic strategy: mirror the dealer rule - hit until score reaches 17 or more.
        return (score < 17);

    case Difficulty::Hard:
    {
        // Probability-aware: only hit if the bust chance is below the threshold.
        // The 40% threshold is a common heuristic in basic Blackjack strategy.
        const double BUST_THRESHOLD = 0.40;
        double risk = ProbabilityCalc::bustChance(score, deck);
        return (risk < BUST_THRESHOLD);
    }
    }
    return false;
}

std::string CPUPlayer::difficultyName() const
{
    switch (m_difficulty)
    {
    case Difficulty::Easy:
        return "Easy";
    case Difficulty::Medium:
        return "Medium";
    case Difficulty::Hard:
        return "Hard";
    }
    return "Unknown";
}
