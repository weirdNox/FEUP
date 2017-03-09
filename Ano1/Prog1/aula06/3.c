#include <stdio.h>

int main()
{
    int var1 = 5;
    char var2 = 'a';
    int *ptr1 = &var1;
    char *ptr2 = &var2;
    *ptr2 = 'b';
    printf("var1 tem o endereco %p e o valor %d\n", ptr1, *ptr1);
    printf("var2 tem o endereco %p e o valor %d\n", ptr2, *ptr2);
    printf("Sizeof:\n\tchar: %zu\n\tchar *: %zu\n\tint: %zu\n\tint *: %zu\n", sizeof(char),
           sizeof(char *), sizeof(int), sizeof(int *));
    printf("ptr1 e ptr1+1: %p %p\nptr2 e ptr2+1: %p %p\n", ptr1, ptr1+1, ptr2, ptr2+1);

    return 0;
}
