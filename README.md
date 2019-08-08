# Postgraduate-c
考研c语言试题


### 1. 转换文件中的字母大小写

假设某操作系统有一条命令，该命令的功能是将指定文本文件中的所有小写字母都转换成为大写字母，其他字符格式保持不变。命令格式为:

`change  filename`

其中，`change`为命令名，参数 `filename` 为文本文件名。请编写实现该命令的程序，要求要进行命令行的正确性检查。

```c
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("缺少文件名参数\n");
        return 1;
    }

    FILE * fp = fopen(argv[1], "r+");

    int c;
    while((c = fgetc(fp)) != EOF){
        if (c >= 97 && c <= 122) {
            c -= 32;                    // 将大写字母转换为小写字母
            fseek(fp, -1, SEEK_CUR);    // 将指针回退一格
            fputc(c, fp);               // 用转换后的大写字母覆盖掉原来的小写字母
        }
    }

    fclose(fp); // close the file

    return 0;
}

```


### 2. 请编写一程序，该程序对于任意输入的正整数 n，输出 n 以内的所有素数。（n>=2）

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int n= 0;

	if (argc > 1) {
		// 如果命令行有输入的参数，则从命令行获取
		n = atoi(argv[1]);	// 命令行的数字字符串需要用 atoi 函数转换成 int 类型
	}else{
		printf("请输入一个正整数：");
		scanf("%d", &n);
	}

	if (n < 2) {
		printf("输入不正确：%d\n", n);
		return 1;
	}

	printf("您输入的数是：%d, %d以内的素数有：\n", n, n);
	int a = 0;
	int row = 0;
	for (int i=1; i<=n; i++) {
		for(int j=2; j<i; j++) {
			if (i % j == 0) a++;
		}
		if (a == 0) {
			if (5 == row) {
				printf("\n");
				row = 0;
			}
			printf("%d\t", i);
			row++;
		}else{
			a = 0;
		}
	}
	printf("\n");
	return 0;
}

```

### 3. 写一个类似 linux 的 tail 命令的程序

```c
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

```

