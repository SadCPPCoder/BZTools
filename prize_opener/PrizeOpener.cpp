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

#include "PrizeOpener.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <random>

#define MAX_INPUT_LINE_LEN  ( 256 )
#define CANDIDATE_SEPERATOR ( ',' )
#define PRIZE_SEPERATOR     ( '*' )
#define COMMENT_CHAR        ( '#' )
#define INVALID_CANDIDATE_NO    ( 0 )

PrizeOpener::PrizeOpener()
: mConfig( "" )
{

}

PrizeOpener::~PrizeOpener()
{

}

bool PrizeOpener::ReadCandidates()
{
    if( !mConfig.ParseConfig() )
    {
        return false;
    }

    std::ifstream infile( mConfig.CandidateInfoPath().c_str() );
    if( !infile.is_open() )
    {
        std::cerr << "Open file failed, path [" << mConfig.CandidateInfoPath() << "]." << std::endl;
        return false;
    }

    char line[MAX_INPUT_LINE_LEN] = {0};
    std::string strLine;
    std::size_t pos;
    int lineNo = 1;
    while( !infile.eof() )
    {
        if( infile.getline( line, MAX_INPUT_LINE_LEN ).eof() )
        {
            break;
        }
        else if( !infile.good() )
        {
            std::cerr << "Read candidate failed!\n";
            infile.close();
            return false;
        }

        strLine = line;
        pos = strLine.find_last_of( CANDIDATE_SEPERATOR );
        if( std::string::npos == pos )
        {
            std::cerr << "Bad candidate information [" << strLine << "], line: " 
                    << lineNo << "." << std::endl;
            infile.close();
            return false;
        }

        CandidateInfo candidate( strLine.substr( 0, pos ), 
                             std::stoi( strLine.substr( pos+1 ) ) );

        if( 0 == candidate.Name().compare( "None Name" ) )
        {
            std::cerr << "Invalid candidate info [" << strLine
                << "], line: " << lineNo << std::endl;
            infile.close();
            return false;
        }

        // ToDo: check repeat
        
        // insert
        mCandidateInfoList.push_back( candidate );
        
        ++lineNo;
    }

    infile.close();
    return true;
}

bool PrizeOpener::ReadPrizes()
{
    if( !mConfig.ParseConfig() )
    {
        return false;
    }

    std::ifstream infile( mConfig.PrizeInfoPath().c_str() );
    if( !infile.is_open() )
    {
        std::cerr << "Open file failed, path [" << mConfig.PrizeInfoPath() << "]." << std::endl;
        return false;
    }

    char line[MAX_INPUT_LINE_LEN] = {0};
    std::string strLine;
    std::size_t pos;
    int lineNo = 1;
    while( !infile.eof() )
    {
        if( infile.getline( line, MAX_INPUT_LINE_LEN ).eof() )
        {
            break;
        }
        else if( !infile.good() )
        {
            std::cerr << "Read prize failed!\n";
            infile.close();
            return false;
        }
        strLine = line;

        pos = strLine.find_first_not_of( " \t" );
        if( std::string::npos == pos || COMMENT_CHAR == strLine[pos] )
        {
            continue;
        }

        pos = strLine.find_last_of( PRIZE_SEPERATOR );
        if( std::string::npos == pos )
        {
            std::cerr << "Bad prize information [" << strLine << "], line: " 
                    << lineNo << "." << std::endl;
            infile.close();
            return false;
        }

        PrizeInfo prize( strLine.substr( 0, pos ), 
                             std::stoi( strLine.substr( pos+1 ) ) );

        if( 0 == prize.Name().compare( "XXXX" ) )
        {
            std::cerr << "Invalid candidate info [" << strLine
                << "], line: " << lineNo << std::endl;
            infile.close();
            return false;
        }

        // ToDo: check repeat
        
        // insert
        mPrizeInfoVec.push_back( prize );
        
        ++lineNo;
    }

    infile.close();
    return true;
}

bool PrizeOpener::OpenPrize
    (
    const int timeSeed,
    const int prizeIndex
    )
{
    if( prizeIndex >= mPrizeInfoVec.size() || 
        mPrizeInfoVec[prizeIndex].IsOpened() )
    {
        return false;
    }

    std::default_random_engine seedEngine( timeSeed );
    std::uniform_int_distribution<int> distribution( 9, 99999 );
    std::default_random_engine ownerEngine( distribution( seedEngine ) );
    std::uniform_int_distribution<int> ownerDistribution( 0, mCandidateInfoList.size() - 1 );
    auto randomOneOwner = [&] ()
    {
        return ownerDistribution( ownerEngine );
    };

    int ownerIndex = 0;
    auto itCandidate = mCandidateInfoList.begin();
    for( int i = 0; i < mPrizeInfoVec[prizeIndex].Num(); ++i )
    {
        // open one prize
        ownerIndex = randomOneOwner();

        // create prize onwer
        itCandidate = mCandidateInfoList.begin();
        std::advance( itCandidate, ownerIndex );
        PrizeOwnerInfo ownerInfo( itCandidate->Name(), itCandidate->No() );
        ownerInfo.SetPrize( mPrizeInfoVec[prizeIndex].Name() );

        std::cout << ownerInfo.GetPrize() << std::endl;

        mPrizeOwnerInfoList.push_back( ownerInfo );

        mCandidateInfoList.erase( itCandidate );
    }

    mPrizeInfoVec[prizeIndex].SetOpened( true );

    return true;
}

const std::vector<PrizeInfo>& PrizeOpener::Prizes()
{
    return mPrizeInfoVec;
}

const std::list<PrizeOwnerInfo>& PrizeOpener::Owners()
{
    return mPrizeOwnerInfoList;
}

