#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <math.h>

#define PARENT_PROCESS "dad.exe"

enum PIPES { READ, WRITE }; /* Constants 0 and 1 for READ and WRITE */
#define NUMPROBLEM 8

int main(int argc, char *argv[]){
    if( argc != 2 ){
        printf("Child process must have pipe read handle.\n");
        printf("You should run '%s' instead.\n", PARENT_PROCESS);
        return -1;
    }
    
    int hpipe[2];
    int problem, c;
    
    /* Convert passed string handle to integer handle. */
    hpipe[READ] = atoi( argv[1] );
    
    /* Read problem from pipe and calculate solution. */
    for( c = 0; c < NUMPROBLEM; c++ )
    {
        read(
            hpipe[READ],
            (char *)&problem,
            sizeof( int )
        );
        
        printf( 
            "Dad, the square root of %d is %3.2f.\n",
            problem, 
            sqrt( ( double )problem )
        );
    }
}
