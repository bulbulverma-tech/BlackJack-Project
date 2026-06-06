#include "GameEngine.h"
#include "ScoreManager.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <ctime>

// Prints the ASCII banner shown at startup.
static void printBanner() {
    std::cout << "\n";
    std::cout << "  ======================================\n";
    std::cout << "        BLACKJACK  -  SIT102 Project    \n";
    std::cout << "  ======================================\n\n";
}

// Asks the player to pick a CPU difficulty and returns the matching enum value.
static Difficulty chooseDifficulty() {
    std::cout << "  Select CPU difficulty:\n";
    std::cout << "    1) Easy   - random decisions\n";
    std::cout << "    2) Medium - hits below 17 (dealer rules)\n";
    std::cout << "    3) Hard   - uses live bust probability\n";
    std::cout << "  Choice (1/2/3): ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") return Difficulty::Easy;
    if (input == "3") return Difficulty::Hard;
    return Difficulty::Medium;  // Default to Medium for any other input
}

int main() {
    // Seed the random number generator used by Easy difficulty
    srand((unsigned)time(NULL));

    printBanner();

    ScoreManager scores("scores.txt");
    scores.load();

    if (scores.hasHistory()) {
        std::cout << "  Past sessions:\n";
        scores.display();
    } else {
        std::cout << "  No past sessions found - starting fresh!\n\n";
    }

    Difficulty diff = chooseDifficulty();

    GameEngine engine(diff, scores);
    engine.run();

    return 0;
}