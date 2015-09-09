#pragma once

#include "Position.h"

#include <vector>
#include <memory>

class Board;

class AbstractAction
{
public:
    virtual ~AbstractAction() {}

    virtual void Apply(Board& board) = 0;
    virtual void Revert(Board& board) = 0;
};

class CompositeAction : public AbstractAction
{
public:
    virtual ~CompositeAction() {}

    void AddAction(std::unique_ptr<AbstractAction> action);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    std::vector<std::unique_ptr<AbstractAction>> m_actions;
};

class AddAction : public AbstractAction
{
public:
    virtual ~AddAction() {}

    AddAction(Position position, Stone stone, Position previousLastPosition);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    Position m_position;
    Stone m_stone = Stone::Black;
    
    Position m_previousLastPosition;
};

class RemoveAction : public AbstractAction
{
public:
    virtual ~RemoveAction() {}

    RemoveAction(Position position, Stone stone);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    Position m_position;
    Stone m_stone = Stone::Black;
};

class PassAction : public AbstractAction
{
public:
    virtual ~PassAction() {}

    PassAction() = default;

    virtual void Apply(Board&) override {}
    virtual void Revert(Board&) override {}
};