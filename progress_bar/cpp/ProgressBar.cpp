/****************************************************
 * File: ProgressBar.hpp
 * Description: This is a C++ API to provide the UI
 *      of a progress bar in console or the file.
 *
 *  Author: Zhang Bob
 *  Date: 2019.01.02
 ***************************************************/

#include "ProgressBar.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

ProgressBar::ProgressBar()
    : mProgressVal( 0.0 )
    , mProgressTotalVal( 0.0 )
    , mProgressBarType( PROGRESS_BAR_CONSOLE )
{
}

ProgressBar::ProgressBar
    (
    const PROGRESS_BAR_TYPE aType,
    const double aTotal,
    const std::string &aFilePath
    )
    : mProgressVal( 0.0 )
    , mProgressTotalVal( aTotal )
    , mProgressBarType( aType )
{
    InitProgressBar( aType, aTotal, aFilePath );
}

ProgressBar::~ProgressBar()
{
    if( mUIThread.joinable() )
    {
        mUIThread.join();
    }

    mOutFile.close();
}

bool ProgressBar::InitProgressBar
    (
    const PROGRESS_BAR_TYPE aType,
    const double aTotal,
    const std::string &aFilePath
    )
{
    mProgressBarType = aType;

    if( PROGRESS_BAR_FILE == mProgressBarType )
    {
        mOutFile.open( aFilePath.c_str(), std::ios::out);
    }
}

 bool ProgressBar::UpdateProgressBar
    (
     const double aVal
    )
{
    if( aVal > mProgressTotalVal )
    {
        return true;
    }

    mProgressVal = aVal;

    // Update the progress bar
    switch( mProgressBarType )
    {
    case PROGRESS_BAR_FILE:
        {
            // TODO: to update the progress bar in the file.
        }
        break;

    case PROGRESS_BAR_CONSOLE:
        {
            // to update the progress bar in the std::cout
            // Backspace
            for( int i=0; i<PROGRESS_BUF_LEN; ++i )
            {
                std::cout << '\b';
            }   

            // refresh the progress bar
            std::string progressBarStr;
            bool ret = GenerateProgressBar( mProgressVal, progressBarStr );
            std::cout << progressBarStr;
            std::cout.flush();

            if( ret )
            {
                return true;
            }
        }
        break;

    defalut:
        std::cerr << "Wrong type of progress bar, type: [" << mProgressBarType << "].\n";
        break;
    }

    return false;
}

bool ProgressBar::UpdateProgressVal
    (
    const double aVal
    )
{
    mProgressVal = aVal;
}

void ProgressBar::StartProgressThread
    (
    const int aTime
    )
{
    // TODO: start a thread and the flush time
    // of the progress bar is the aTime.
}

bool ProgressBar::GenerateProgressBar
    (
    const double aVal,
    std::string &aProgressBarStr
    )
{
    if( aVal > mProgressTotalVal )
    {
        mProgressVal = mProgressTotalVal;
    }
    else
    {
        mProgressVal = aVal;
    }

    // Make the progress bar
    std::stringstream progressBarSS;
    // First boarder  
    progressBarSS << PBarBoarderLeftChar;

    // Calculate the progress 
    double ratio = mProgressVal / mProgressTotalVal * 100;
    int count = static_cast<int>( ratio );
    for( int i=0; i<PROGRESS_BAR_LEN; ++i )
    {
        if( i <= count )
        {
            progressBarSS << PBarProgressChar;
        }
        else
        {
            progressBarSS << PBarEmptyChar;
        }
    }

    // Second boarder
    progressBarSS << PBarBoarderRightChar;

    // Third boarder
    progressBarSS << PBarBoarderLeftChar;

    // Output ratio
    progressBarSS << std::setfill( ' ' ) << std::setw( PROGRESS_VAL_LEN ) << std::fixed << std::setprecision( 1 ) << ratio;
    
    // Ratio sign and Forth boarder
    progressBarSS << PBarRatioChar << PBarBoarderRightChar;

    aProgressBarStr = progressBarSS.str();
    if( mProgressVal == mProgressTotalVal )
    {
        return true;
    }

    return false;    
}
