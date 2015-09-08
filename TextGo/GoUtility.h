#pragma once

#include "Position.h"

#include <vector>

class Board;

std::vector<Position> GetAdjacentSpaces(Board board, Position position, Stone stone);
std::vector<Position> GetGroup(Board board, Position position);
unsigned int GetGroupLiberties(Board board, Position position);