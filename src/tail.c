#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

int tail( char* filename, unsigned int n )
{
    FILE* f = fopen( filename, "r" );

    if ( !f )
    {
        printf( "Can not open the file: %s\n", filename );
        return 1;
    }

    fseek( f, -1, SEEK_END );                   /* SEEK_END位置是一个无效的位置，对于文件而言，SEEK_END的前一个位置是文件中最后的那个数据的位置 */
    unsigned int num = 0;
    while ( 1 )
    {
        if ( fgetc( f ) == '\n' )
        {
            if ( ++num > n )
                break;
        }
        if ( fseek( f, -2, SEEK_CUR ) != 0 )    /* 当读取好一个字符串后，文件的指针会移动到下一个位置上，所以要倒序读取，此时文件的指针需要向前移动2个字节 */
        {
            fseek( f, 0, SEEK_SET );            /* 如果fseek返回值不是零，说明已经到达的文件的头部，该文件需要从头全部输出 */
            break;
        }
    }

    char buffer[BUFSIZE];
    while ( fgets( buffer, BUFSIZE, f ) )       /* 此处没有用feof判断，因为用feof判断会导致最后一行输出两次，feof是在文件指针失效后，还要读取一次才判断为真 */
    {
        printf( "%s", buffer );
    }
    return 0;
}


int main( int argc, char** argv )
{
    char* file_name;
    unsigned int n = 10;

    int i = 0;
    while ( ++i < argc )
    {
        if ( 0 == strcmp( argv[i], "-n" ) && (i + 1) < argc )
        {
            n = atoi( argv[++i] );
        }else{
            file_name = argv[i];
        }
    }

    if ( file_name == NULL )
    {
        printf( "Please input a filename\n" );
        return 1;
    }

    return tail( file_name, n );
}

