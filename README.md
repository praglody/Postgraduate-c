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
			if (5 == row++) {
				printf("\n");
				row = 0;
			}
			printf("%d\t", i);
		}else{
			a = 0;
		}
	}
	printf("\n");
	return 0;
}

```

