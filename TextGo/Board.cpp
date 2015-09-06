#include "Board.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

bool operator<(const Position& left, const Position& right)
{
    return std::make_tuple(left.GetY(), left.GetX()) < std::make_tuple(right.GetY(), right.GetX());
}

bool Board::Place(Position position, Stone stone)
{
    auto find = m_stones.find(position);
    if (find == end(m_stones))
    {
        m_stones[position] = stone;
        m_lastPlace = position;

        return true;
    }
    else
    {
        return false;
    }
}

void Board::Print() const
{
    std::string board =

        "    a   b   c   d   e   f   g   h   j   k   l   m   n   o   p   q   r   s   t    "   "\n"
        "19  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  19"   "\n"
        "                                                                                 "   "\n"
        "18  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  18"   "\n"
        "                                                                                 "   "\n"
        "17  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  17"   "\n"
        "                                                                                 "   "\n"
        "16  .   .   .   o   .   .   .   .   .   o   .   .   .   .   .   o   .   .   .  16"   "\n"
        "                                                                                 "   "\n"
        "15  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  15"   "\n"
        "                                                                                 "   "\n"
        "14  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  14"   "\n"
        "                                                                                 "   "\n"
        "13  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  13"   "\n"
        "                                                                                 "   "\n"
        "12  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  12"   "\n"
        "                                                                                 "   "\n"
        "11  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  11"   "\n"
        "                                                                                 "   "\n"
        "10  .   .   .   o   .   .   .   .   .   o   .   .   .   .   .   o   .   .   .  10"   "\n"
        "                                                                                 "   "\n"
        " 9  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   9"   "\n"
        "                                                                                 "   "\n"
        " 8  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   8"   "\n"
        "                                                                                 "   "\n"
        " 7  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   7"   "\n"
        "                                                                                 "   "\n"
        " 6  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   6"   "\n"
        "                                                                                 "   "\n"
        " 5  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   5"   "\n"
        "                                                                                 "   "\n"
        " 4  .   .   .   o   .   .   .   .   .   o   .   .   .   .   .   o   .   .   .   4"   "\n"
        "                                                                                 "   "\n"
        " 3  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   3"   "\n"
        "                                                                                 "   "\n"
        " 2  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   2"   "\n"
        "                                                                                 "   "\n"
        " 1  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   1"   "\n"
        "                                                                                 "   "\n"
        "    a   b   c   d   e   f   g   h   j   k   l   m   n   o   p   q   r   s   t    "   "\n";

    auto GetStoneStringPosition = [](Position position) -> unsigned int
        {
            return ((position.GetY() * 82 * 2) + 82) + ((position.GetX() * 4) + 4);
        };

    for (const auto& stonePosition : m_stones)
    {
        board.replace(GetStoneStringPosition(stonePosition.first) - 1, 3, "(0)");
    }

    if (!m_stones.empty())
    {
        auto find = m_stones.find(m_lastPlace);
        if (find != end(m_stones))
        {
            board.replace(GetStoneStringPosition(find->first), 1, "^");
        }
    }

    std::vector<std::string> boardSections;
    std::vector<std::tuple<std::string, Stone>> stoneSections;

    if (!m_stones.empty())
    {
        unsigned int currentPosition = 0;
        for (const auto& stonePosition : m_stones)
        {
            unsigned int stoneStringPosition = GetStoneStringPosition(stonePosition.first);
            
            std::string boardSection = board.substr(currentPosition, (stoneStringPosition - 1) - currentPosition);
            std::string stoneSection = board.substr(stoneStringPosition - 1, 3);

            boardSections.push_back(boardSection);
            stoneSections.push_back(std::make_tuple(stoneSection, stonePosition.second));

            currentPosition = stoneStringPosition + 2;
        }

        if (!board.empty())
        {
            boardSections.push_back(board.substr(currentPosition));
        }
    }
    else
    {
        boardSections.push_back(board);
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0, j = 0; i < boardSections.size() || j < stoneSections.size(); ++i, ++j)
    {
        SetConsoleTextAttribute(hConsole, 8);
        std::cout << boardSections[i];

        if (j < stoneSections.size())
        {
            if (std::get<1>(stoneSections[j]) == Stone::Black)
            {
                SetConsoleTextAttribute(hConsole, 9);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 15);
            }

            std::cout << std::get<0>(stoneSections[j]);
        }
    }
}

Stone Board::GetStoneAt(Position position) const
{
    auto find = m_stones.find(position);
    if (find != end(m_stones))
    {
        return find->second;
    }
    else
    {
        return Stone::None;
    }
}