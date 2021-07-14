#include <stdio.h>
#include "cli.h"

int func_a(int argc, const char **argv)
{
    printf("In A function:\n");

    for (int i = 0; i < argc; i++)
    {
        printf(" [%d] ==> %s\n", i, argv[i]);
    }

    return 0;
}

int func_b(int argc, const char **argv)
{
    printf("In B function:\n");

    for (int i = 0; i < argc; i++)
    {
        printf(" [%d] --- %s\n", i, argv[i]);
    }

    return 0;
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
    add_cli_cmd("fun-b", "Second defined function", func_b);

    while(1){
        char c = getchar();

        if (c == '\n') {
            return parse_cli();
        } else {
            put_cli_char(c);
        }
    }

    return 0;
}