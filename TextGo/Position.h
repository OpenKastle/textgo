#pragma once

#include <map>
#include <tuple>

enum class Stone
{
    None,
    Black,
    White
};

class Position
{
public:
    Position() = default;
    Position(unsigned int x, unsigned int y);
    Position(const std::string& positionString);
    ~Position() = default;

    unsigned int GetX() const { return m_x; }
    unsigned int GetY() const { return m_y; }

    bool Valid() const;

    std::string ToString() const;

private:
    unsigned int m_x = 99;
    unsigned int m_y = 99;
};

bool operator<(const Position& left, const Position& right);
bool operator==(const Position& a, const Position& b);