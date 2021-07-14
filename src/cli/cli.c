#include "cli.h"

#define CLI_ENTRIES ((CLI_CMD_ENTRIES_MAX) + 1)
#if (CLI_CMD_BUFFER_SIZE < 2)
#error The CLI_CMD_BUFFER_SIZE MUST BE AT LEAST 2
#endif
#if (CLI_CMD_ENTRIES_MAX < 1)
#error The CLI_CMD_ENTRIES_MAX MUST BE AT LEAST 1
#endif
#if (CLI_CMD_PARAMS_MAX < 1)
#error The CLI_CMD_PARAMS_MAX MUST BE AT LEAST 1
#endif

typedef struct
{
    const char *cmd;
    const char *help;
    int (*cb)(int, const char **);
} cli_entry_t;

static struct cli_entries_t
{
    cli_entry_t entries[CLI_ENTRIES];
    int cnt;
} cli_entries;

static struct cli_buffer_t
{
    char content[CLI_CMD_BUFFER_SIZE];
    int size;
} cli_buffer;

static struct cli_params_t
{
    const char *params[CLI_CMD_PARAMS_MAX];
    int cnt;
} cli_params;

static void (*print_cb)(const char *);

static int help_cmd(int argc, const char **argv)
{
    for (int i = 0; i < cli_entries.cnt; i++)
    {
        print_cb(cli_entries.entries[i].cmd);
        print_cb(" - ");
        print_cb(cli_entries.entries[i].help);
        print_cb("\n");
    }

    return CLI_OK;
}

static void print_invalid_message(void)
{
#if (CLI_PRINT_INVALID_CMD_NOTE)
    print_cb("The entered command: '");
    print_cb(cli_buffer.content);
    print_cb("' is invalid!\n");
#endif
}

static int are_strings_the_same(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
    {
        if (!*s1)
        {
            return 1;
        }
    }
    return 0;
}

static int execute_buffer(void)
{
    char *ptr = cli_buffer.content;
    cli_params.cnt = 0;

    while (*ptr && (cli_params.cnt < CLI_CMD_PARAMS_MAX))
    {
        while (*ptr && (*ptr == CLI_DELIMITER_CHAR))
        {
            ptr++;
        }

        if (*ptr)
        {
            cli_params.params[cli_params.cnt++] = ptr;
        }
        else
        {
            break;
        }

        while (*ptr && (*ptr != CLI_DELIMITER_CHAR))
        {
            ptr++;
        }

        if (*ptr && (cli_params.cnt < CLI_CMD_PARAMS_MAX))
        {
            *ptr = '\0';
            ptr++;
        }
        else
        {
            break;
        }
    }

    if (cli_params.cnt > 0)
    {
        for (int i = 0; i < cli_entries.cnt; i++)
        {
            if (are_strings_the_same(cli_entries.entries[i].cmd, cli_params.params[0]))
            {
                return cli_entries.entries[i].cb(cli_params.cnt, cli_params.params);
            }
        }
    }

    print_invalid_message();
    return CLI_ERROR_INVALID_CMD;
}

int init_cli(void (*print)(const char *))
{
    if (!print)
    {
        return CLI_ERROR_INVALID_FUNCTION_POINTER;
    }

    cli_entries.cnt = 0;
    print_cb = print;

    for (int i = 0; i < CLI_CMD_BUFFER_SIZE; i++)
    {
        cli_buffer.content[i] = '\0';
    }
    cli_buffer.size = 0;

    return add_cli_cmd(CLI_HELP_CMD, CLI_HELP_CMD_HELP, help_cmd);
}

int add_cli_cmd(const char *cmd_string, const char *help_string, int (*cmd_cb)(int, const char **))
{
    if (!cmd_cb)
    {
        return CLI_ERROR_INVALID_FUNCTION_POINTER;
    }
    else if (cli_entries.cnt < CLI_ENTRIES)
    {
        cli_entries.entries[cli_entries.cnt].cmd = cmd_string;
        cli_entries.entries[cli_entries.cnt].help = help_string;
        cli_entries.entries[cli_entries.cnt].cb = cmd_cb;
        cli_entries.cnt++;
        return CLI_OK;
    }
    else
    {
        return CLI_ERROR_CMD_REGISTER_FAILED;
    }
}

int put_cli_char(char c)
{
    if (cli_buffer.size < (CLI_CMD_BUFFER_SIZE - 1))
    {
        cli_buffer.content[cli_buffer.size++] = c;
        cli_buffer.content[cli_buffer.size] = '\0';
        return CLI_OK;
    }
    else
    {
        return CLI_ERROR_BUFFER_OVERFLOW;
    }
}

int parse_cli(void)
{
    int result = execute_buffer();

    cli_buffer.content[0] = '\0';
    cli_buffer.size = 0;

    return result;
}