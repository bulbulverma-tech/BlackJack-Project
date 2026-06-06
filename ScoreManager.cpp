#include "ScoreManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

double SessionResult::winRate() const
{
    int total = totalGames();
    return total > 0 ? static_cast<double>(wins) / total : 0.0;
}

ScoreManager::ScoreManager(const std::string &filename) : m_filename(filename) {}

// Reads sessions from the file.
// File format (one session per line, comma-separated):
//   wins,losses,draws,difficulty
void ScoreManager::load()
{
    std::ifstream file(m_filename);
    if (!file.is_open())
        return; // First run - no file yet, that is fine

    m_sessions.clear();
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        SessionResult s;
        char delim;
        std::istringstream iss(line);
        // Parse: wins,losses,draws,difficulty
        if (iss >> s.wins >> delim >> s.losses >> delim >> s.draws >> delim)
        {
            std::getline(iss, s.difficulty);
        }
        // Prepend so newest sessions appear first in the list
        m_sessions.push_front(s);
    }
}

// Appends one session line to the end of the scores file.
void ScoreManager::save(const SessionResult &result)
{
    std::ofstream file(m_filename, std::ios::app); // Open in append mode
    if (!file.is_open())
    {
        std::cerr << "[Warning] Could not open " << m_filename << " for writing.\n";
        return;
    }
    file << result.wins << ","
         << result.losses << ","
         << result.draws << ","
         << result.difficulty << "\n";
}

bool ScoreManager::hasHistory() const
{
    return !m_sessions.empty();
}

void ScoreManager::display() const
{
    if (m_sessions.empty())
    {
        std::cout << "  No previous sessions found.\n";
        return;
    }

    // Sort sessions by win rate descending for a leaderboard view
    auto sorted = std::vector<SessionResult>(m_sessions.begin(), m_sessions.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const SessionResult &a, const SessionResult &b)
              {
                  return a.winRate() > b.winRate();
              });

    std::cout << "\n  +--------+--------+--------+--------+-----------+\n";
    std::cout << "  | Rank   | Wins   | Losses | Draws  | Win Rate  |\n";
    std::cout << "  +--------+--------+--------+--------+-----------+\n";

    int rank = 1;
    for (const auto &s : sorted)
    {
        std::cout << "  | " << std::left << std::setw(7) << rank++
                  << "| " << std::setw(7) << s.wins
                  << "| " << std::setw(7) << s.losses
                  << "| " << std::setw(7) << s.draws
                  << "| " << std::fixed << std::setprecision(1)
                  << (s.winRate() * 100.0) << "%      |\n";
    }
    std::cout << "  +--------+--------+--------+--------+-----------+\n\n";
}
