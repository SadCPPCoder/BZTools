#include "PrizeOpenerUI.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>

bool PrizeOpenerUI::Init()
{
    if( !mOpener.ReadCandidates() )
    {
        return false;
    }

    std::cout << "Read candidates OK!";

    if( !mOpener.ReadPrizes() )
    {
        return false;
    }

    return true;
}

void PrizeOpenerUI::ShowPrizes()
{
    std::cout << "****************************************************************\n"
        << "Total Prizes:\n"
        << std::left << std::setw(10) << "Index" 
        << std::left << std::setw(30) << "Name" 
        << std::left << std::setw(10) << "Num" 
        << std::left << std::setw(10) << "State" 
        << std::endl;
    int index = 0;
    std::for_each( mOpener.Prizes().begin(), mOpener.Prizes().end(), 
                   [&] ( const PrizeInfo& prize )
                   {
                       std::cout << std::left << std::setw(10) << index++
                           << std::left << std::setw(30) << prize.Name()
                           << std::left << std::setw(10) << prize.Num()
                           << std::left << std::setw(10) 
                           << ( prize.IsOpened() ? "Opened" : "Not Open" )
                           << std::endl;
                   } );
}

void PrizeOpenerUI::ShowPrizeOwner()
{
    std::cout << "----------------------------------------------------------------\n"
        << "Current Prize Owner:\n"
        << std::left << std::setw(20) << "Owner Name"
        << std::left << std::setw(15) << "Owner No"
        << std::left << std::setw(30) << "Prize Name"
        << std::endl;
    std::for_each( mOpener.Owners().begin(), mOpener.Owners().end(),
                   [] ( const PrizeOwnerInfo& owner )
                   {
                       std::cout << std::left << std::setw(20) << owner.Name()
                           << std::left << std::setw(15) << owner.No()
                           << std::left << std::setw(30) << owner.GetPrize()
                           << std::endl;
                   } );
    std::cout << "****************************************************************" << std::endl;
}

bool PrizeOpenerUI::CmdParse()
{
    static int prizeIndex = 0;
    static std::chrono::milliseconds startTime, stopTime;
    static bool open_flag = false;
    static bool start_flag = false;
    static std::string strNotice;
    std::string strCmd;
    std::cout << "cmd " << strNotice << ">";
    std::cout.flush();
    std::cin >> strCmd;
    {
        if( !start_flag &&
            0 == strCmd.compare("open") )
        {
            if( open_flag )
            {
                std::cout << "Already in open process!" << std::endl;
                return true;
            }
            std::cout << "Please input the index of prize to be opened: ";
            std::cin >> prizeIndex;
            if( mOpener.Prizes().size() <= prizeIndex )
            {
                std::cerr << "Prize index out of range!\n";
            }
            else if( mOpener.Prizes()[prizeIndex].IsOpened() )
            {
                std::cerr << "This prize already opened!\n";
            }
            else
            {
                std::cout << " Type \"start\" to start open! " << std::endl;
                open_flag = true;
                strNotice = "open " + std::to_string( prizeIndex ) + " ";
            }
        }
        else if( open_flag &&
                 !start_flag &&
                 0 == strCmd.compare("start") )
        {
            startTime = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() );
            strNotice += "start ";
            start_flag = true;
        }
        else if( open_flag &&
                 start_flag &&
                 0 == strCmd.compare("stop") )
        {
            stopTime = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() );
            int seedTime = startTime.count() + stopTime.count();
            mOpener.OpenPrize( seedTime, prizeIndex );
            open_flag = false;
            start_flag = false;
            strNotice = "";
        }
        else if( 0 == strCmd.compare("exit") )
        {
            return false;
        }
        else
        {
            std::cerr << "Error input!" << std::endl;
        }
    }

    return true;
}

void PrizeOpenerUI::Run()
{
    if( !Init() )
    {
        return;
    }

    std::cout << "Init OK!" << std::endl;

    do
    {
        ShowPrizes();
        ShowPrizeOwner();
    } while( CmdParse() );
}
