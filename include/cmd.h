#ifndef CMD_H
#define CMD_H

#include "fields.h"
#include "dllist.h"
#include "text.h" 

/**
 * @brief Enum defining different types of commands that can be processed
 */
typedef enum {
    CMD_WRITE,      /**< Command type for adding content */
    CMD_DELETE,     /**< Command type for deleting content */
    CMD_TO_END,     /**< Command type for moving to end */
    CMD_STOP,       /**< Command type for stopping execution */
    CMD_UNKNOWN     /**< Unknown or unrecognized command type */
} CmdType;

/**
 * @brief Structure representing a command with its properties
 */
typedef struct {
    CmdType type;   /**< Type of the command */
    char* str;      /**< String associated with the command */
    int count;      /**< Count parameter for the command */
} Cmd;

/**
 * @brief Function pointer type for command handlers
 * @param cmd Pointer to the command to be handled
 * @param text Pointer to the text structure being manipulated
 */
typedef void (*CmdHandler)(Cmd*, Text*);

/**
 * @brief Structure mapping command names to their types and handlers
 */
typedef struct {
    const char* command_name; /**< Name of the command as string */
    CmdType type;             /**< Type of the command */
    CmdHandler handler;       /**< Function pointer to handle the command */
} CmdMapping;


void run_cmds(IS is, Text* text);
CmdHandler get_cmd_handler(CmdType type);
void handle_write(Cmd* cmd, Text* text);
void handle_delete(Cmd* cmd, Text* text);
void handle_to_end(Cmd* cmd, Text* text);
void handle_stop(Cmd* cmd, Text* text);

#endif