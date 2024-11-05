#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <math.h>

enum PIPES { READ, WRITE }; /* Constants 0 and 1 for READ and WRITE */
#define NUMPROBLEM 8

#define CHILD_PROCESS "son.exe"

int main(int argc, char *argv[]){
    if( argc > 1 ){
        printf("Parent process must NOT have any command line argument.\n");
        return -1;
    }
    
    int hpipe[2];
    char hstr[20];
    int pid, problem, c;
    int termstat;
    
    setvbuf( stdout, NULL, _IONBF, 0 );

    /* Open a set of pipes */
    if( _pipe( hpipe, 256, O_BINARY ) == -1 )
        exit( 1 );
    
    /* Convert pipe read handle to string and pass as argument
    * to spawned program. Program spawns itself (argv[0]).
    */
    itoa( hpipe[READ], hstr, 10 );
    if( ( pid = spawnl( P_NOWAIT, CHILD_PROCESS, CHILD_PROCESS, hstr, NULL ) ) == -1 )
        printf( "Spawn failed" );
    
    /* Put problem in write pipe. Since spawned program is
    * running simultaneously, first solutions may be done
    * before last problem is given.
    */
    for( problem = 1000; problem <= NUMPROBLEM * 1000; problem += 1000)
    {
        printf(
            "Son, what is the square root of %d?\n",
            problem
        );
        
        write(
            hpipe[WRITE],
            (char *)&problem,
            sizeof( int )
        );
    }
    
    /* Wait until spawned program is done processing. */
    _cwait( &termstat, pid, WAIT_CHILD );
    if( termstat & 0x0 )
        printf( "Child failed\n" );
    
    close( hpipe[READ] );
    close( hpipe[WRITE] );
}
