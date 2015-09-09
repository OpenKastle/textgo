#include "GoUtility.h"

#include "Board.h"

#include <set>
#include <algorithm>

std::vector<Position> GetAdjacentSpaces(Board board, Position position, Stone stone)
{
    std::vector<Position> neighbors;

    // Left
    if (position.GetX() > 0)
    {
        Position left(position.GetX() - 1, position.GetY());
        if (board.GetStoneAt(left) == stone)
        {
            neighbors.push_back(left);
        }
    }

    // Right
    if (position.GetX() < 18)
    {
        Position right(position.GetX() + 1, position.GetY());
        if (board.GetStoneAt(right) == stone)
        {
            neighbors.push_back(right);
        }
    }

    // Up
    if (position.GetY() > 0)
    {
        Position up(position.GetX(), position.GetY() - 1);
        if (board.GetStoneAt(up) == stone)
        {
            neighbors.push_back(up);
        }
    }

    // Down
    if (position.GetY() < 18)
    {
        Position down(position.GetX(), position.GetY() + 1);
        if (board.GetStoneAt(down) == stone)
        {
            neighbors.push_back(down);
        }
    }

    return neighbors;
}

std::vector<Position> GetGroup(Board board, Position position)
{
    Stone color = board.GetStoneAt(position);
    if (color == Stone::None)
    {
        return {};
    }

    std::vector<Position> group;
    std::vector<Position> search;

    search.push_back(position);
    while (!search.empty())
    {
        Position current = search.front();
        group.push_back(current);
        search.erase(begin(search));

        std::vector<Position> adjacentStones = GetAdjacentSpaces(board, current, color);
        for (auto& adjacentStone : adjacentStones)
        {
            if (std::find(begin(group), end(group), adjacentStone) == end(group) &&
                std::find(begin(search), end(search), adjacentStone) == end(search))
            {
                search.push_back(adjacentStone);
            }
        }
    }

    return group;
}

unsigned int GetGroupLiberties(Board board, Position position)
{
    if (board.GetStoneAt(position) == Stone::None)
    {
        return GetAdjacentSpaces(board, position, Stone::Black).size() +
               GetAdjacentSpaces(board, position, Stone::White).size();
    }

    std::vector<Position> group = GetGroup(board, position);
    if (group.empty())
    {
        return GetAdjacentSpaces(board, position, Stone::Black).size() +
               GetAdjacentSpaces(board, position, Stone::White).size();
    }

    std::set<Position> liberties;
    for (const auto& position : group)
    {
        std::vector<Position> adjacentEmptyPositions = GetAdjacentSpaces(board, position, Stone::None);
        liberties.insert(begin(adjacentEmptyPositions), end(adjacentEmptyPositions));
    }

    return liberties.size();
}