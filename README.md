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
        n = atoi(argv[1]);  // 命令行的数字字符串需要用 atoi 函数转换成 int 类型
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

在 Unix 操作系统中有一条命令，命令的功能是打印文本文件的最后 n 行。命令格式为:

tail [-n] filename

其中，tail 为命令名；参数 filename 为文本文件名；参数 [-n] 表示要打印的行数，该参数是可选的，缺省值为10，即无此参数时，表示打印文件的最后10行。例如，命令

tail -20  example.txt

表示打印文本文件 example.txt 的最后 20 行。如果被打印的文本文件中行数少于 n 行或者少于 10 行，该命令将打印文件中的所有行。

请用带参数的 main 函数实现该程序。该程序应该具有一定的错误处理能力，例如，能够处理非法命令参数和非法文件名。

程序中可以使用以下 C 库函数:

- int atoi(char *s) 将数字串转换为相应整数;
- fgets(char *s, int n, FILE *fp)   从文件中读入一行;
- `void* malloc(size_t size);` / `void free(void* p);`  申请和释放内存;
- strlen    计算字符串的长度;
- strcpy    将一个字符串拷贝到另一个字符串中。

除此之外，不允许使用其它库函数。

提示:

1. 可以在命令行参数正确性分析过程中获取被打印的文本文件名称以及需要打印的行数等信息;
2. 如果命令行分析正确，可以建立一个不带头结点的单向循环链表存放从文件中读到的内容。

#### 解答：
- 直接操作文件的实现 [src/tail.c](src/tail.c)
- 使用单向循环链表的实现 [src/tail_by_linked_list.c]


### 4. 计算重复数字的和

请编写程序，该程序首先通过键盘输入获得整型数据 a 与 n, 然后计算 sum=a+aa+aaa+...(共n项)，最后输出计算结果。例如:当 a=5, n=4 时计算 sum=5+55+555+5555。

#### 解答：
- [src/sumRepeatNum.c](src/sumRepeatNum.c)

