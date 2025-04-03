#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"
#include "text.h"

/**
 * @brief Array of command mappings from string names to their handlers
 * Last element has NULL name to mark end of array
 */
static CmdMapping command_mappings[] = {
    {"write:", CMD_WRITE, handle_write},    /**< Mapping for WRITE command */
    {"delete:", CMD_DELETE, handle_delete}, /**< Mapping for DELETE command */
    {"to_end:", CMD_TO_END, handle_to_end}, /**< Mapping for TO_END command */
    {"stop:", CMD_STOP, handle_stop},       /**< Mapping for STOP command */
    {NULL, CMD_UNKNOWN, NULL}               /**< Sentinel to mark end of mappings */
};

/**
 * @brief Implementation of WRITE command handler
 * Adds content to the text according to command parameters
 * @param cmd Command containing string and count to add
 * @param text Text structure to add content to
 */
void handle_write(Cmd* cmd, Text* text) { write(text, cmd->str, cmd->count); }

/**
 * @brief Implementation of DELETE command handler
 * Deletes content from the text according to command parameters
 * @param cmd Command containing string and count to delete
 * @param text Text structure to delete content from
 */
void handle_delete(Cmd* cmd, Text* text) { del(text, cmd->str, cmd->count); }

/**
 * @brief Implementation of TO_END command handler
 * Moves cursor to the end of the text
 * @param cmd Command (not used)
 * @param text Text structure to operate on
 */
void handle_to_end(Cmd* cmd, Text* text) { to_end(text); }

/**
 * @brief Implementation of STOP command handler
 * Stops the command processing loop
 * @param cmd Command (not used)
 * @param text Text structure (not used)
 */
void handle_stop(Cmd* cmd, Text* text) {}

/**
 * @brief Retrieves the handler function for a given command type
 * @param type The command type to find handler for
 * @return Pointer to the handler function, or NULL if not found
 */
CmdHandler get_cmd_handler(CmdType type) 
{
    for (int i = 0; command_mappings[i].command_name != NULL; i++) 
    {
        if (command_mappings[i].type == type) 
            return command_mappings[i].handler;
    }
    return NULL;
}

/**
 * @brief Main command processing loop
 * Reads and executes commands from input stream
 * @param is Input stream containing commands
 * @param text Text structure to operate on
 */
void run_cmds(IS is, Text* text) 
{
    while (get_line(is) >= 0) 
    {
        const char* command_str = is->fields[0];
        CmdType type = CMD_UNKNOWN;
        CmdHandler handler = NULL;

        for (int i = 0; command_mappings[i].command_name != NULL; i++) 
        {
            if (!strcmp(command_str, command_mappings[i].command_name)) 
            {
                type = command_mappings[i].type;
                handler = command_mappings[i].handler;
                break;
            }
        }

        if (type == CMD_UNKNOWN) 
        {
            printf("An undefined command is found at line %d. Skipping...\n", is->line);
            continue;
        }
        
        if (type == CMD_STOP) 
        {
            handler(NULL, text);
            break;
        }
        
        if (type == CMD_TO_END) 
        {
            Cmd cmd = {type, NULL, 0};
            if (handler)
                handler(&cmd, text);
        }

        else 
        {
            for (int i = 1; i < is->NF; i += 2) 
            {
                if (i + 1 >= is->NF) break;

                int count = atoi(is->fields[i]);
                char* str = strdup(is->fields[i + 1]);

                Cmd cmd = {type, str, count};
                if (handler) 
                    handler(&cmd, text);
                
                free(str); 
            }
        }
    }
}