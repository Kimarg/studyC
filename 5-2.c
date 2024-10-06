#include <stdio.h>
#include <string.h>

int main()
{
    char src[100];
    char dest[100];
    int result;
    gets(src);
    gets(dest);
    
    result = strcmp(src, dest);
    printf("result = %d\n",result);
    return 0;
}
