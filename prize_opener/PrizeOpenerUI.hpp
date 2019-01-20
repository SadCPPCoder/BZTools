#pragma once

#include "PrizeOpener.hpp"

class PrizeOpenerUI
{
public:
    void Run();
private:
    bool Init();

    void ShowPrizes();

    void ShowPrizeOwner();

    bool CmdParse();

    PrizeOpener mOpener;
};
