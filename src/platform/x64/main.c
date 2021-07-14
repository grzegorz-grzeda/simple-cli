#include <stdio.h>
#include "cli.h"

int func_a(int argc, char **argv)
{
    printf("In func_a:\n");

    for (int i = 0; i < argc; i++)
    {
        printf(" [%d] = %s\n", i, argv[i]);
    }
}

int func_b(int argc, char **argv)
{
    printf("In func_a:\n");

    for (int i = 0; i < argc; i++)
    {
        printf(" [%d] = %s\n", i, argv[i]);
    }
}

void print(const char *text)
{
    printf("%s", text);
}

int main(void)
{
    printf("SIMPLE CLI example software\n");
    printf("Type 'help' command to get help\n");

    init_cli(print);
    add_cli_cmd("fun-a", "First defined function", func_a);
    add_cli_cmd("fun-b", "Second defined function", func_a);

    while (parse_cli_char(getchar()) > 0)
        ;

    return 0;
}