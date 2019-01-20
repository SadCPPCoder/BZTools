/******************************************************
 * File:
 *      PrizeOwnerInfo.cpp
 * Description:
 *      This file defines the information of prize owner.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#include "PrizeOwnerInfo.hpp"

PrizeOwnerInfo::PrizeOwnerInfo
    (
    const std::string& name,
    const unsigned int& no
    )
    : CandidateInfo( name, no )
    , mPrize()
{
}

PrizeOwnerInfo::PrizeOwnerInfo
    (
    const PrizeOwnerInfo& ownerInfo
    )
    : CandidateInfo( ownerInfo.Name(), ownerInfo.No() )
    , mPrize( ownerInfo.GetPrize() )
{
}

PrizeOwnerInfo::PrizeOwnerInfo
    (
    const PrizeOwnerInfo&& ownerInfo
    )
    : CandidateInfo( ownerInfo )
    , mPrize( ownerInfo.GetPrize() )
{
}

void PrizeOwnerInfo::SetPrize
    (
    const std::string& prize
    )
{
    mPrize = std::string( prize );
}

const std::string& PrizeOwnerInfo::GetPrize() const
{
    return mPrize;
}
