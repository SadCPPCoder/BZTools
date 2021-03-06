#include <chrono>
#include <iomanip>
#include <iostream>
#include "ProgressBar.hpp"

int main( int argc, char **argv )
{
    const int totalVal = 150;

    ProgressBar progressBar( PROGRESS_BAR_CONSOLE, totalVal, "" );

    for( int curVal=0; curVal<=totalVal; ++curVal )
    {
        progressBar.UpdateProgressBar( curVal );
        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
        //std::cout << std::endl;
    }
    std::cout << std::endl;
}

