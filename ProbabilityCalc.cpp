#include "ProbabilityCalc.h"
#include <sstream>
#include <iomanip>
#include <cmath>

// Core probability calculation.
// We count how many cards in the remaining deck would push (currentScore + card.value) over 21.
// That count divided by total remaining cards gives P(bust).
//
// Discrete Maths link: this is a direct application of classical probability -
//   P(event) = |favourable outcomes| / |sample space|
// where the sample space is the set of remaining cards (no replacement).
double ProbabilityCalc::bustChance(int currentScore, const Deck &deck)
{
    const auto &remaining = deck.cards();
    if (remaining.empty())
        return 0.0;

    int bustCount = 0;
    for (const auto &card : remaining)
    {
        // An ace drawn as 11 may reduce to 1 inside Hand::recalculate(),
        // but we conservatively assume it is added at face value here.
        // This gives a slight overestimate for aces, which is the safe/cautious choice.
        if (currentScore + card.value > 21)
        {
            ++bustCount;
        }
    }

    return static_cast<double>(bustCount) / static_cast<double>(remaining.size());
}

std::string ProbabilityCalc::bustMessage(int currentScore, const Deck &deck)
{
    double pct = bustChance(currentScore, deck) * 100.0;
    std::ostringstream oss;
    oss << "  [Odds] If you hit: " << std::fixed << std::setprecision(1) << pct << "% bust chance";
    return oss.str();
}
