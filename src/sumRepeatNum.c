#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
    if ( argc < 3 )
    {
        printf( "参数不正确\n" );
        return 1;
    }

    int     a   = atoi( argv[1] );
    int     n   = atoi( argv[2] );
    long long int   sum = 0;

    if ( a > 9 || n < 0 )
    {
        printf( "参数不正确\n" );
        return 1;
    }

    for ( int i = 0; i < n; i++ )
    {
        sum += sum * 10 + a;
    }

    printf( "sum = %lld\n", sum );
    return 0;
}

