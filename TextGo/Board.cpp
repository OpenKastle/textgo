#include "Board.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

bool operator<(const Position& left, const Position& right)
{
    return std::make_tuple(left.GetY(), left.GetX()) < std::make_tuple(right.GetY(), right.GetX());
}

Board::Board()
    : m_colorScheme(std::make_unique<RealisticColorScheme>())
{
}

Board::Board(std::unique_ptr<ColorScheme> colorScheme)
    : m_colorScheme(std::move(colorScheme))
{
}

Board::Board(const Board& other)
    : m_stones(other.m_stones),
      m_lastPosition(other.m_lastPosition),
      m_colorScheme(other.m_colorScheme->Clone())
{
}

Board& Board::operator=(const Board& other)
{
    m_stones = other.m_stones;
    m_lastPosition = other.m_lastPosition;
    m_colorScheme = other.m_colorScheme->Clone();

    return *this;
}

bool Board::Add(Position position, Stone stone, bool recordLast)
{
    auto find = m_stones.find(position);
    if (find == end(m_stones))
    {
        m_stones[position] = stone;

        if (recordLast)
        {
            m_lastPosition = position;
        }

        return true;
    }
    else
    {
        return false;
    }
}

void Board::Remove(Position position)
{
    m_stones.erase(position);
}

void Board::Print() const
{
    std::string board =

        "    A   B   C   D   E   F   G   H   J   K   L   M   N   O   P   Q   R   S   T    "   "\n"
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
        "    A   B   C   D   E   F   G   H   J   K   L   M   N   O   P   Q   R   S   T    "   "\n";

    for (const auto& stonePosition : m_stones)
    {
        board.replace(GetStoneStringPosition(stonePosition.first) - 1, 3, "(O)");
    }

    if (!m_stones.empty())
    {
        auto find = m_stones.find(m_lastPosition);
        if (find != end(m_stones))
        {
            board.replace(GetStoneStringPosition(find->first), 1, "^");
        }
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::map<unsigned int, WORD> sections = GetBoardTextSections();
    for (auto iter = begin(sections); iter != end(sections); ++iter)
    {
        auto nextIter = iter;
        ++nextIter;

        SetConsoleTextAttribute(hConsole, iter->second);
        if (nextIter != end(sections))
        {
            std::cout << board.substr(iter->first, nextIter->first - iter->first);
        }
        else
        {
            std::cout << board.substr(iter->first);
        }
    }
}

unsigned int Board::GetStoneStringPosition(Position position) const
{
    return ((position.GetY() * 82 * 2) + 82) + ((position.GetX() * 4) + 4);
}

std::map<unsigned int, WORD> Board::GetBoardTextSections() const
{
    std::map<unsigned int, WORD> sections;

    sections[0] = m_colorScheme->GetBoardLabelAttributes();

    for (unsigned int i = 0; i < 38; ++i)
    {
        sections[82 + (i * 82) +  3] = m_colorScheme->GetBoardAttributes();
        sections[82 + (i * 82) + 78] = m_colorScheme->GetBoardLabelAttributes();
    }

    for (const auto& stonePosition : m_stones)
    {
        unsigned int stoneTextPosition = GetStoneStringPosition(stonePosition.first);

        sections[stoneTextPosition - 1]
            = (stonePosition.second == Stone::Black)
                ? m_colorScheme->GetBlackStoneAttributes()
                : m_colorScheme->GetWhiteStoneAttributes();

        if (stonePosition.first.GetX() != 18)
        {
            sections[stoneTextPosition + 2] = m_colorScheme->GetBoardAttributes();
        }
    }

    return sections;
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

void Board::SetLastPosition(Position position)
{
    m_lastPosition = position;
}
