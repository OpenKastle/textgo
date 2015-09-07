#include "ColorSchemes.h"

#include <windows.h>

WORD BasicColorScheme::GetBoardAttributes() const
{
    return FOREGROUND_INTENSITY;
}

WORD BasicColorScheme::GetBoardLabelAttributes() const
{
    return FOREGROUND_INTENSITY;
}

WORD BasicColorScheme::GetBlackStoneAttributes() const
{
    return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
}

WORD BasicColorScheme::GetWhiteStoneAttributes() const
{
    return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
}

std::unique_ptr<ColorScheme> BasicColorScheme::Clone() const
{
    return std::make_unique<BasicColorScheme>(*this);
}

WORD RealisticColorScheme::GetBoardAttributes() const
{
    return BACKGROUND_RED | BACKGROUND_GREEN;
}

WORD RealisticColorScheme::GetBoardLabelAttributes() const
{
    return FOREGROUND_INTENSITY;
}

WORD RealisticColorScheme::GetBlackStoneAttributes() const
{
    return GetBoardAttributes();
}

WORD RealisticColorScheme::GetWhiteStoneAttributes() const
{
    return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | GetBoardAttributes();
}

std::unique_ptr<ColorScheme> RealisticColorScheme::Clone() const
{
    return std::make_unique<RealisticColorScheme>(*this);
}