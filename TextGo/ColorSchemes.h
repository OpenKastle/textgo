#pragma once

#include <windows.h>
#include <memory>

class ColorScheme
{
public:
    virtual ~ColorScheme() {}

    virtual WORD GetBoardAttributes() const = 0;
    virtual WORD GetBoardLabelAttributes() const = 0;
    virtual WORD GetBlackStoneAttributes() const = 0;
    virtual WORD GetWhiteStoneAttributes() const = 0;

    virtual std::unique_ptr<ColorScheme> Clone() const = 0;
};

class BasicColorScheme : public ColorScheme
{
public:
    virtual ~BasicColorScheme() override {}

    virtual WORD GetBoardAttributes() const override;
    virtual WORD GetBoardLabelAttributes() const override;
    virtual WORD GetBlackStoneAttributes() const override;
    virtual WORD GetWhiteStoneAttributes() const override;

    virtual std::unique_ptr<ColorScheme> Clone() const override;
};

class RealisticColorScheme : public ColorScheme
{
public:
    virtual ~RealisticColorScheme() override {}

    virtual WORD GetBoardAttributes() const override;
    virtual WORD GetBoardLabelAttributes() const override;
    virtual WORD GetBlackStoneAttributes() const override;
    virtual WORD GetWhiteStoneAttributes() const override;

    virtual std::unique_ptr<ColorScheme> Clone() const override;
};