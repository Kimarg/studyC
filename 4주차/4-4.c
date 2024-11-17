/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int ch;
    char message[100];
    int i = 0;
    while((ch = getchar()) != '\n'){
        message[i++] = ch;
        
    }
    message[i] = '\0';
    printf("%s",message);
    return 0;
}
