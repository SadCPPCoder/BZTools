/******************************************************
 * File:
 *      CandidateInfo.hpp
 * Description:
 *      This file defines the information of candidate.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#pragma once

#include <string>

class CandidateInfo
{
public:
    CandidateInfo
        (
        const std::string& candidateName,
        const unsigned int& candidateNo
        );

    CandidateInfo
        (
        const CandidateInfo& candidate
        );

    CandidateInfo
        (
        const CandidateInfo&& candidate
        );

    const std::string& Name() const;
    
    const unsigned int& No() const;
protected:
    std::string mCandidateName;
    unsigned int mCandidateNo;
};
