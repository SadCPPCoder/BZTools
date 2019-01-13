#include <chrono>
#include <iostream>
#include "ProgressBar.hpp"

int main()
{
    int totalVal = 210;
    ProgressBar progressBar( PROGRESS_BAR_FILE, totalVal, "./progress_bar.txt" );
    progressBar.StartProgressThread( 500 );

    for( int curVal=0; curVal<=totalVal; ++curVal )
    {
        std::cout << "Set the progress val[" << curVal << "]" << std::endl;

        progressBar.UpdateProgressVal( curVal );

        std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    }

    return 0;
}

