#include <windows.h>

class
{
public:
    virtual WORD GetBoardAttributes() const = 0;
    virtual WORD GetBoardLabelAttributes() const = 0;
    virtual WORD GetBlackStoneAttributes() const = 0;
    virtual WORD GetWhiteStoneAttributes() const = 0;
};