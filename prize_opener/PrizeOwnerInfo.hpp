/******************************************************
 * File:
 *      PrizeOwnerInfo.hpp
 * Description:
 *      This file defines the information of prize owner.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#pragma once

#include "CandidateInfo.hpp"

class PrizeOwnerInfo: public CandidateInfo
{
public:
    PrizeOwnerInfo
        (
        const std::string& name,
        const unsigned int& no
        );
    PrizeOwnerInfo
        (
        const PrizeOwnerInfo& ownerInfo
        );
    PrizeOwnerInfo
        (
        const PrizeOwnerInfo&& ownerInfo
        );
    void SetPrize( const std::string& prize );
    const std::string& GetPrize() const;
private:
    std::string mPrize;
};

