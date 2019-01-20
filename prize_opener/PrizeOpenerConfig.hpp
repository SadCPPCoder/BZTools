/******************************************************
 * File:
 *      PrizeOpenerConfig.hpp
 * Description:
 *      This file defines the configure parser of prizes
 *      opener.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#pragma once

#include <string>

class PrizeOpenerConfig
{
public:
    PrizeOpenerConfig() {}; 

    PrizeOpenerConfig
        (
        const std::string& configPath
        );

    bool ParseConfig();

    const std::string& CandidateInfoPath();

    const std::string& PrizeInfoPath();

    const bool Finished();
private:
    bool        mParsedFlag;
    std::string mConfigFilePath;

    std::string mCandidateInfoFilePath;

    std::string mPrizeInfoFilePath;
};

