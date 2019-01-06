/****************************************************
 * File: ProgressBar.hpp
 * Description: This is a C++ API to provide the UI
 *      of a progress bar in console or the file.
 *
 *  Author: Zhang Bob
 *  Date: 2019.01.02
 ***************************************************/

#ifndef PROGRES_BAR_HPP
#define PROGRES_BAR_HPP

#include <fstream>
#include <string>
#include <thread>

#define PROGRESS_BAR_LEN        (100)
#define PROGRESS_VAL_LEN        (5)
#define PROGRESS_BUF_LEN        (PROGRESS_BAR_LEN + PROGRESS_VAL_LEN + 5) //100+2+2+5+1

// define the symbols.
const char PBarBoarderLeftChar = '[';
const char PBarBoarderRightChar = ']';
const char PBarEmptyChar = ' ';
const char PBarProgressChar = '#';
const char PBarRatioChar = '%';

// define the type of the progress bar
typedef enum
{
    PROGRESS_BAR_CONSOLE = 1,
    PROGRESS_BAR_FILE,
} PROGRESS_BAR_TYPE;

class ProgressBar
{
public:
    ProgressBar();

    ProgressBar
        (
        const PROGRESS_BAR_TYPE aType,
        const double aTotal,
        const std::string &aFilePath
        );

    ~ProgressBar();

    // Init a progress bar, if it's type is file, we should assign a file path.
    bool InitProgressBar
        (
        const PROGRESS_BAR_TYPE aType,
        const double aTotal,
        const std::string &aFilePath
        );

    // Call this function to update progress bar in the user thread.
    bool UpdateProgressBar
        (
        const double aVal
        );

    // Call this function to update progress value in user thread, but the UI output is in the
    // progress bar object's thread.
    bool UpdateProgressVal
        ( 
        const double aVal
        );

    // Call this function in the user thread, and then the progress bar object will start a thread
    // to update the progress bar's UI.
    void StartProgressThread
        (
        const int aTime 
        );

private:
    // Generate the progress bar information
    bool GenerateProgressBar
        ( 
        const double aVal,
        std::string &aProgressBarStr 
        );

private:
    std::thread       mUIThread;
    double            mProgressVal;
    double            mProgressTotalVal;
    PROGRESS_BAR_TYPE mProgressBarType;
    std::ofstream     mOutFile;
};

#endif
