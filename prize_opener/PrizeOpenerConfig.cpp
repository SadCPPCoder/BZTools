/******************************************************
 * File:
 *      PrizeOpenerConfig.cpp
 * Description:
 *      This file defines the configure parser of prizes
 *      opener.
 * Author:
 *      Bob Zhang
 * Date:
 *      20190119
 ******************************************************/

#include "PrizeOpenerConfig.hpp"
#include <iostream>
#include <fstream>
#include <map>

#define CONFIG_FILE_PATH    ( "./prize_opener.conf" )

PrizeOpenerConfig::PrizeOpenerConfig
    (
    const std::string& configPath
    )
    : mConfigFilePath( configPath )
    , mParsedFlag( false )
{
}

bool PrizeOpenerConfig::ParseConfig()
{
    if( mParsedFlag )
    {
        return true;
    }

    if( mConfigFilePath.empty() )
    {
        mConfigFilePath = CONFIG_FILE_PATH;
    }

    std::ifstream configFile( mConfigFilePath.c_str() );
    if( !configFile.is_open() )
    {
        std::cerr << "Open config file failed, path[" << CONFIG_FILE_PATH << "]\n";
        return false;
    }
    char line[255] = { '0' };
    std::string strLine;
    std::size_t pos;
    std::map<std::string, std::string> configMap;
    while( configFile.getline( line, 255 ).good() )
    {
        strLine = line;
        
        pos = strLine.find_first_not_of( " \t" );
        // # or blank line
        if( std::string::npos == pos || '#' == strLine[pos] )
        {
            // it a comment, jump this line
            continue;
        }

        pos = strLine.find_first_of( '=' );
        if( std::string::npos == pos )
        {
            std::cerr << "Error config item [" << strLine << "].\n";
            return false;
        }

        configMap.insert( std::make_pair<std::string, std::string>( 
                    strLine.substr(0, pos), strLine.substr( pos+1 ) ) );
    }

    if( !configFile.eof() && !configFile.good() )
    {
        std::cerr << "Read config file failed, path[" << CONFIG_FILE_PATH << "]\n";
        return false;
    }

    configFile.close();

    mCandidateInfoFilePath = configMap["CandidateInfoFile"];
    if( mCandidateInfoFilePath.empty() )
    {
        std::cerr << "CandidateInfoFile is not configured!\n";
        return false;
    }

    mPrizeInfoFilePath = configMap["PrizeInfoFile"];
    if( mPrizeInfoFilePath.empty() )
    {
        std::cerr << "PrizeInfoFile is not configured!\n";
        return false;
    }

    mParsedFlag = true;

    return true;
}

const std::string& PrizeOpenerConfig::CandidateInfoPath()
{
    return mCandidateInfoFilePath;
}

const std::string& PrizeOpenerConfig::PrizeInfoPath()
{
    return mPrizeInfoFilePath;
}

const bool PrizeOpenerConfig::Finished()
{
    return mParsedFlag;
}

