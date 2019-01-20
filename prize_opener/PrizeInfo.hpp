/******************************************************
 * File:
 *      PrizeInfo.hpp
 * Description:
 *      This file defines the information of prizes.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#pragma once

#include <string>

class PrizeInfo
{
public:
    PrizeInfo
        (
        const std::string& prizeName,
        const unsigned int& prizeNum
        );

    PrizeInfo
        (
        const PrizeInfo& prizeInfo
        );

    const std::string& Name() const;

    const int& Num() const;
    
    void SetOpened
        ( 
        bool flag
        );

    const bool IsOpened() const;
private:
    std::string mPrizeName;
    int         mPrizeNum;
    bool        mOpenFlag;
};

