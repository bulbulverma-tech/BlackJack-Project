#include "GameEngine.h"
#include "ProbabilityCalc.h"
#include <iostream>
#include <string>
#include <limits>

GameEngine::GameEngine(Difficulty cpuDifficulty, ScoreManager &scoreManager)
    : m_cpu(cpuDifficulty), m_scores(scoreManager) {}

void GameEngine::printDivider() const
{
    std::cout << "  --------------------------------------------------\n";
}

// Main loop: keep playing rounds until the player types 'q'.
void GameEngine::run()
{
    std::cout << "\n  CPU difficulty: " << m_cpu.difficultyName() << "\n";
    std::cout << "  Cards remaining in deck: " << m_deck.remaining() << "\n\n";

    while (true)
    {
        printDivider();
        std::cout << "  Press ENTER to play a round, or 'q' + ENTER to quit: ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "q" || input == "Q")
            break;

        // Re-shuffle if the deck drops below 15 cards to keep odds meaningful
        if (m_deck.remaining() < 15)
        {
            std::cout << "  [Deck reshuffled]\n";
            m_deck = Deck();
        }

        playRound();
        std::cout << "\n  Session score  -  You: " << m_playerWins
                  << "  CPU: " << m_cpuWins
                  << "  Draws: " << m_draws << "\n";
    }

    // Save this session to the scores file before exiting
    SessionResult result{m_playerWins, m_cpuWins, m_draws, m_cpu.difficultyName()};
    m_scores.save(result);
    std::cout << "\n  Session saved. Thanks for playing!\n\n";
}

void GameEngine::playRound()
{
    Hand playerHand, cpuHand;

    // Deal two cards each, alternating (standard Blackjack dealing order)
    playerHand.addCard(m_deck.deal());
    cpuHand.addCard(m_deck.deal());
    playerHand.addCard(m_deck.deal());
    cpuHand.addCard(m_deck.deal());

    // Show initial hands - CPU's first card is hidden
    std::cout << "\n  Your hand:  ";
    playerHand.display();
    std::cout << "  CPU hand:   ";
    cpuHand.display(/*hideFirst=*/true);
    std::cout << "  Your score: " << playerHand.score() << "\n";

    // Check for player Blackjack before any turns
    if (playerHand.isBlackjack())
    {
        std::cout << "\n  BLACKJACK! You win this round!\n";
        ++m_playerWins;
        return;
    }

    playerTurn(playerHand);

    // Only play the CPU turn if the player has not already bust
    if (!playerHand.isBust())
    {
        cpuTurn(cpuHand);
        evaluate(playerHand, cpuHand);
    }
}

// Prompts the player repeatedly until they stand or bust.
void GameEngine::playerTurn(Hand &playerHand)
{
    while (true)
    {
        // Show live bust probability - the key HD feature
        std::cout << ProbabilityCalc::bustMessage(playerHand.score(), m_deck) << "\n";

        std::cout << "  Hit (h) or Stand (s)? ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "h" || choice == "H")
        {
            playerHand.addCard(m_deck.deal());
            std::cout << "\n  Your hand:  ";
            playerHand.display();
            std::cout << "  Your score: " << playerHand.score() << "\n\n";

            if (playerHand.isBust())
            {
                std::cout << "  BUST! You exceeded 21. CPU wins this round.\n";
                ++m_cpuWins;
                return;
            }
            if (playerHand.score() == 21)
            {
                std::cout << "  You hit 21!\n";
                return;
            }
        }
        else
        {
            // Any non-'h' input is treated as Stand
            std::cout << "  You stand at " << playerHand.score() << ".\n";
            return;
        }
    }
}

// CPU draws cards based on its difficulty strategy.
void GameEngine::cpuTurn(Hand &cpuHand)
{
    std::cout << "\n  CPU reveals hand: ";
    cpuHand.display();
    std::cout << "  CPU score: " << cpuHand.score() << "\n";

    while (m_cpu.shouldHit(cpuHand, m_deck))
    {
        cpuHand.addCard(m_deck.deal());
        std::cout << "  CPU hits  -> ";
        cpuHand.display();
        std::cout << "  CPU score: " << cpuHand.score() << "\n";

        if (cpuHand.isBust())
        {
            std::cout << "  CPU busts!\n";
            return;
        }
    }

    if (!cpuHand.isBust())
    {
        std::cout << "  CPU stands at " << cpuHand.score() << ".\n";
    }
}

// Compares final scores and declares the winner.
void GameEngine::evaluate(const Hand &playerHand, const Hand &cpuHand)
{
    int ps = playerHand.score();
    int cs = cpuHand.score();

    printDivider();
    std::cout << "  RESULT - Your score: " << ps << "  |  CPU score: "
              << (cpuHand.isBust() ? "BUST" : std::to_string(cs)) << "\n";

    if (cpuHand.isBust() || ps > cs)
    {
        std::cout << "  You WIN this round!\n";
        ++m_playerWins;
    }
    else if (ps == cs)
    {
        std::cout << "  DRAW.\n";
        ++m_draws;
    }
    else
    {
        std::cout << "  CPU wins this round.\n";
        ++m_cpuWins;
    }
}
