#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv )
{
    int i = 0;
    char bar[102];
    const char *lable = "|/-\\";
    bar[0] = 0;
    printf("Hello, world!\n");
    printf("The progress of task: \n");
    while( i <= 100 )
    {
        // In linux '/r' is to return the begin of the line.
        printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
        fflush(stdout);
        bar[i] = '#';
        ++i;
        bar[i] = 0;
        usleep(100000);
    }
    printf("\n");
}
