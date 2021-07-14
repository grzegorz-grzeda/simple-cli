#include "cli.h"

#define CLI_ENTRIES ((CLI_CMD_ENTRIES_MAX) + 1)
#if (CLI_CMD_BUFFER_SIZE < 1)
# error The CLI_CMD_BUFFER_SIZE MUST BE AT LEAST 1
#endif
#if (CLI_CMD_ENTRIES_MAX < 1)
# error The CLI_CMD_ENTRIES_MAX MUST BE AT LEAST 1
#endif
#if (CLI_CMD_PARAMS_MAX < 1)
# error The CLI_CMD_PARAMS_MAX MUST BE AT LEAST 1
#endif

typedef struct
{
    const char *cmd;
    const char *help;
    int (*cb)(int, char **);
} cli_entry_t;

struct cli_buffer_t
{
    char content[CLI_CMD_BUFFER_SIZE];
    int size;
} cli_buffer;
static cli_entry_t entries[CLI_ENTRIES];
static int cmd_cnt = 0;

static void (*print_cb)(const char *);

static int help_cmd(int argc, char **argv)
{
    for (int i = 0; i < cmd_cnt; i++)
    {
        print_cb(entries[i].cmd);
        print_cb(" - ");
        print_cb(entries[i].help);
        print_cb("\n");
    }

    return 0;
}

static void print_invalid_message(void){
    print_cb("The command: ");
    print_cb(cli_buffer.content);
    print_cb(" is invalid!\n");
}

static int execute_buffer(void)
{
    const char *params[CLI_CMD_PARAMS_MAX];
    int params_cnt = 0;

    print_invalid_message();
    help_cmd(0,0);
    return 0;
}

int init_cli(void (*print)(const char *))
{
    cmd_cnt = 0;
    print_cb = print;

    for (int i = 0; i < CLI_CMD_BUFFER_SIZE; i++)
        cli_buffer.content[i] = '\0';

    return add_cli_cmd("help", "Displays this help", help_cmd);
}

int add_cli_cmd(const char *cmd_string, const char *help_string, int (*cmd_cb)(int, char **))
{
    if (cmd_cnt < CLI_ENTRIES)
    {
        entries[cmd_cnt].cmd = cmd_string;
        entries[cmd_cnt].help = help_string;
        entries[cmd_cnt].cb = cmd_cb;
        cmd_cnt++;
        return 0;
    }
    else
    {
        return -1;
    }
}

int parse_cli_char(char c)
{
    if (c == CLI_EXECUTE_CHAR)
    {
        int result = execute_buffer();
        
        cli_buffer.size = 0;
        
        return result;
    }
    else
    {
        if (cli_buffer.size < (CLI_CMD_BUFFER_SIZE - 1))
        {
            cli_buffer.content[cli_buffer.size++] = c;
            cli_buffer.content[cli_buffer.size] = '\0';
            return 1;
        }
        else
        {
            return -1;
        }
    }
    return 1;
}