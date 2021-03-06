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

    AddAction(Position position, Stone stone);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    Position m_position;
    Stone m_stone = Stone::Black;
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

class LastStoneChange : public AbstractAction
{
public:
    virtual ~LastStoneChange() {}

    LastStoneChange(Position oldPosition, Position newPosition);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    Position m_oldPosition;
    Position m_newPosition;
};

class PassAction : public AbstractAction
{
public:
    virtual ~PassAction() {}

    PassAction() = default;

    virtual void Apply(Board&) override {}
    virtual void Revert(Board&) override {}
};

class CaptureAction : public AbstractAction
{
public:
    virtual ~CaptureAction() {}

    CaptureAction(Stone color, unsigned int captures);

    virtual void Apply(Board& board) override;
    virtual void Revert(Board& board) override;

private:
    Stone m_color = Stone::Black;
    unsigned int m_captures = 0;
};