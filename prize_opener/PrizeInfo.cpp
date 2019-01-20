
/******************************************************
 * File:
 *      PrizeInfo.cpp
 * Description:
 *      This file defines the information of prizes.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#include "PrizeInfo.hpp"

PrizeInfo::PrizeInfo
    (
    const std::string& prizeName,
    const unsigned int& prizeNum
    )
    : mPrizeName( prizeName )
    , mPrizeNum( prizeNum )
    , mOpenFlag( false )
{
    if( prizeName.empty() )
    {
        mPrizeName = "XXXX";
        mPrizeNum = 0;
    }
}

PrizeInfo::PrizeInfo
    (
    const PrizeInfo& prizeInfo
    )
    : mPrizeName( prizeInfo.Name() )
    , mPrizeNum( prizeInfo.Num() )
    , mOpenFlag( false )
{
    if( prizeInfo.Name().empty() )
    {
        mPrizeName = "XXXX";
        mPrizeNum = 0;
    }
}

const std::string& PrizeInfo::Name() const
{
    return mPrizeName;
}

const int& PrizeInfo::Num() const
{
    return mPrizeNum;
}

const bool PrizeInfo::IsOpened() const
{
    return mOpenFlag;
}

void PrizeInfo::SetOpened
    ( 
    bool flag
    )
{
    mOpenFlag = flag;
}

