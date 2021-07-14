#ifndef SIMPLE_CLI_H__
#define SIMPLE_CLI_H__

/**
 * @addtogroup simple-cli Simple CLI
 * Simple CLI module
 * @{
 */

#define CLI_CMD_BUFFER_SIZE 100 /**< Command string buffer size */
#define CLI_CMD_ENTRIES_MAX 10 /**< Number of commands to be handled */
#define CLI_CMD_PARAMS_MAX 10 /**< Delimiterable parameters */
#define CLI_DELIMITER_CHAR ' ' /**< Delimiter character */

#define CLI_PRINT_INVALID_CMD_NOTE 1 /**< Decide if print to output a note about invalid command */

#define CLI_HELP_CMD "help"
#define CLI_HELP_CMD_HELP "Displays this help screen"

#define CLI_OK (0)
#define CLI_ERROR_CMD_REGISTER_ERROR (-100)
#define CLI_ERROR_INVALID_CMD (-101)
#define CLI_ERROR_BUFFER_OVERFLOW (-102)

/**
 * Initialize the CLI
 * @param[in] print Calback to string printer
 * @return CLI_OK if success
 * @return CLI_ERROR_CMD_REGISTER_ERROR if no space for help command (check CLI_CMD_ENTRIES_MAX value)
 */
int init_cli(void (*print)(const char *));

/**
 * Add a command to the CLI
 * @param[in] cmd_string command name to be recognised
 * @param[in] help_string help text to be printed in the help command
 * @param[in] cmd_cb callback to execute the command
 * @return value of the cmd_cb if parsed successfully
 * @return CLI_ERROR_INVALID_CMD if command not recognised
 */
int add_cli_cmd(const char *cmd_string, const char* help_string, int (*cmd_cb)(int, const char **));

/**
 * Put a character into the CLI buffer
 * 
 * @param[in] c char to be put
 * @return CLI_OK if success
 * @return CLI_ERROR_BUFFER_OVERFLOW if no more space in CLI buffer
 */
int put_cli_char(char c);

/**
 * Parse the CLI buffer and try to execute a command
 * 
 * @return value returned by the executed command
 * @return CLI_ERROR_INVALID_CMD if the command in the buffer was not recognised
 */
int parse_cli(void);

/**
 * @}
 */

#endif
