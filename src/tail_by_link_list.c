#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 5

typedef struct List_t
{
    struct List_t* next;
    unsigned int length;
    char* data;
} List;

int tail_by_link_list(char* filename, unsigned int n);

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
        }
        else
        {
            file_name = argv[i];
        }
    }
    if ( file_name == NULL )
    {
        printf( "Usage tail -n filename \n" );
        return 1;
    }
    return tail_by_link_list( file_name, n );
}

int tail_by_link_list(char* filename, unsigned int n)
{
    FILE* f = fopen(filename, "r");
    if ( !f )
    {
        printf("Can not open the file: %s", filename);
        return 1;
    }
    // 为链表分配内存
    List* head = (List*)malloc(sizeof(List));
    List* cursor = head;
    (*cursor).data = (char*)malloc(BUFSIZE * sizeof(char));
    (*cursor).length = BUFSIZE * sizeof(char);
    (*cursor).data[0] = '\0';
    for (int i = 1; i < n; i++)
    {
        cursor = (*cursor).next = (List*)malloc(sizeof(List));
        (*cursor).data = (char*)malloc(BUFSIZE * sizeof(char));
        (*cursor).length = BUFSIZE * sizeof(char);
        (*cursor).data[0] = '\0';
    }
    cursor = (*cursor).next = head;
    char buffer[BUFSIZE];
    char flag = 0;  //是否跳到下一行
    int i;
    while (fgets(buffer, BUFSIZE, f))
    {
        if (flag == 1)
        {
            //将指针指向下一行，并进行清理
            flag = 0;
            cursor = (*cursor).next;
            (*cursor).data[0] = '\0';
        }
        i = 0;
        while (i < BUFSIZE)
        {
            if (buffer[i] == 'n')
            {
                flag = 1;   //本行结束，下次需要指向下一行进行写入
                i += 2;
                break;
            }
            i++;
        }
        if ((*cursor).length >= strlen((*cursor).data) + i)
        {
            // 当前data内存空间足够
            memcpy((*cursor).data + strlen((*cursor).data), buffer, i);
        }
        else
        {
            (*cursor).data = (char *)realloc((*cursor).data, (*cursor).length + i);
            memcpy((*cursor).data + strlen((*cursor).data), buffer, i);
            (*cursor).length += i;
        }
    }
    cursor = head;
    for (i = 0; i < n; i++)
    {
        if (*(*cursor).data == '\0')
        {
            return 0;
        }
        printf("%s", (*cursor).data);
        cursor = (*cursor).next;
    }
    return 0;
}

