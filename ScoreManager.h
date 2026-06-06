#pragma once
#include <string>
#include <list>

// Holds a single session's result (one full sitting at the table).
struct SessionResult
{
    int wins;
    int losses;
    int draws;
    std::string difficulty; // CPU difficulty level used

    int totalGames() const { return wins + losses + draws; }
    double winRate() const; // Returns win rate as 0.0–1.0; 0 if no games played
};

// Manages loading, saving, and displaying historical session results.
// Results are persisted to a plain-text file (scores.txt) using fstream.
//
// In memory, sessions are stored in a std::list<SessionResult> - a doubly-linked
// list - demonstrating an advanced data structure beyond arrays/vectors.
// This makes prepending new sessions O(1) (no element shifting required).
class ScoreManager
{
public:
    explicit ScoreManager(const std::string &filename = "scores.txt");

    void load();                            // Reads all past sessions from the file
    void save(const SessionResult &result); // Appends a new session result to the file
    void display() const;                   // Prints the leaderboard to the terminal

    bool hasHistory() const;

private:
    std::string m_filename;
    std::list<SessionResult> m_sessions; // In-memory session history (linked list)

    // Formats one session row for display
    void printRow(const SessionResult &s) const;
};
