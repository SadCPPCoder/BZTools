/******************************************************
 * File:
 *      PrizeOpener.hpp
 * Description:
 *      This file defines the prizes opener.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#pragma once

#include <list>
#include <string>
#include <vector>
#include "CandidateInfo.hpp"
#include "PrizeInfo.hpp"
#include "PrizeOwnerInfo.hpp"
#include "PrizeOpenerConfig.hpp"

class PrizeOpener
{
public:
    PrizeOpener();

    ~PrizeOpener();

    bool ReadCandidates();

    bool ReadPrizes();

    bool OpenPrize
        (
        const int timeSeed,
        const int prizeIndex
        );

    const std::vector<PrizeInfo>& Prizes();
    const std::list<PrizeOwnerInfo>& Owners();
private:
    PrizeOpenerConfig mConfig;
    std::vector<PrizeInfo> mPrizeInfoVec;
    std::list<CandidateInfo> mCandidateInfoList;
    std::list<PrizeOwnerInfo> mPrizeOwnerInfoList;
};
