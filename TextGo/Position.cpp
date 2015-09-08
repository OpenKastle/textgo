#include "Position.h"

#include <sstream>
#include <cctype>

bool operator<(const Position& left, const Position& right)
{
    return std::make_tuple(left.GetY(), left.GetX()) < std::make_tuple(right.GetY(), right.GetX());
}

bool operator==(const Position& a, const Position& b)
{
    return a.GetX() == b.GetX() &&
           a.GetY() == b.GetY();
}

Position::Position(unsigned int x, unsigned int y)
    : m_x(x),
      m_y(y)
{
}

Position::Position(const std::string& positionString)
{
    if (positionString.size() != 2 && positionString.size() != 3)
    {
        return;
    }

    char letter = positionString[0];
    if (!std::isalpha(letter))
    {
        return;
    }

    letter = std::toupper(letter);

    if (letter == 'I')
    {
        return;
    }

    if (letter > 'T')
    {
        return;
    }

    int y = 0;
    try
    {
        y = std::stoi(positionString.substr(1));
    }
    catch(std::exception e)
    {
        return;
    }

    if (y < 1 || y > 19)
    {
        return;
    }

    unsigned int position = letter - 'A';
    if (position > 8)
        --position;

    m_y = 18 - (y - 1);
    m_x = position;
}

bool Position::Valid() const
{
    if (m_x < 19 || m_y < 19)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Position::ToString() const
{
    char letter = m_x + 'A';
    if (letter >= 'I')
        ++letter;

    std::ostringstream oss;
    oss << static_cast<char>(m_x + 'A') << ((18 - m_y) + 1);

    return oss.str();
}