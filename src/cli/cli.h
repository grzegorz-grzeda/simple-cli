#ifndef SIMPLE_CLI_H__
#define SIMPLE_CLI_H__

#define CLI_CMD_BUFFER_SIZE 100 /**< Command string buffer size */
#define CLI_CMD_ENTRIES_MAX 10 /**< Number of commands to be handled */
#define CLI_CMD_PARAMS_MAX 10 /**< Delimiterable parameters */
#define CLI_DELIMITER_CHAR ' ' /**< Delimiter character */
#define CLI_EXECUTE_CHAR '\n'

int init_cli(void (*print)(const char *));
int add_cli_cmd(const char *cmd_string, const char* help_string, int (*cmd_cb)(int, char **));
int parse_cli_char(char c); 

#endif
