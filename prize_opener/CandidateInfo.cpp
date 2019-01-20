/******************************************************
 * File:
 *      CandidateInfo.cpp
 * Description:
 *      This file defines the information of candidate.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#include "CandidateInfo.hpp"

CandidateInfo::CandidateInfo
    (
    const std::string& candidateName,
    const unsigned int& candidateNo
    )
    : mCandidateName( candidateName )
    , mCandidateNo( candidateNo )
{
    if( candidateName.empty() )
    {
        mCandidateName = "None Name";
        mCandidateNo = 0;
    }
}

CandidateInfo::CandidateInfo
    (
    const CandidateInfo& candidate
    )
    : mCandidateName( candidate.Name() )
    , mCandidateNo( candidate.No() )
{
    if( candidate.Name().empty() )
    {
        mCandidateName = "None Name";
        mCandidateNo = 0;
    }
}

CandidateInfo::CandidateInfo
    (
    const CandidateInfo&& candidate
    )
    : mCandidateName( candidate.Name() )
    , mCandidateNo( candidate.No() )
{

}


const std::string& CandidateInfo::Name() const
{
    return mCandidateName;
}

const unsigned int& CandidateInfo::No() const
{
    return mCandidateNo;
}

