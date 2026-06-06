#pragma once
#include "Deck.h"
#include "Hand.h"
#include "CPUPlayer.h"
#include "ScoreManager.h"

// Orchestrates one full session of Blackjack (many rounds until the player quits).
// Owns the deck, hands, CPU opponent, and score tracker.
class GameEngine
{
public:
    GameEngine(Difficulty cpuDifficulty, ScoreManager &scoreManager);

    // Starts the main game loop - keeps playing rounds until the player chooses to quit.
    void run();

private:
    Deck m_deck;
    CPUPlayer m_cpu;
    ScoreManager &m_scores;

    // Per-session counters
    int m_playerWins = 0;
    int m_cpuWins = 0;
    int m_draws = 0;

    // Plays one full round: deal, player turn, CPU turn, evaluate.
    void playRound();

    // Player's interactive turn - prompts hit/stand, shows live odds.
    void playerTurn(Hand &playerHand);

    // CPU's automated turn - uses CPUPlayer::shouldHit().
    void cpuTurn(Hand &cpuHand);

    // Determines and prints the winner; updates session counters.
    void evaluate(const Hand &playerHand, const Hand &cpuHand);

    // Prints a divider line for a cleaner terminal layout.
    void printDivider() const;
};
