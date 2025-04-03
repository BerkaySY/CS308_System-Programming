#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "cmd.h"
#include "text.h"

/**
 * @brief Main entry point of the program
 * Processes commands from an input file and saves results to an output file
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return 0 on success, non-zero on failure
 */
int main(int argc, char **argv)
{
    if (!check_args(argc, argv))
        exit(1);
    
    File* file = open_file(argv[1]);
    if (file == NULL) {
        exit(1);
    }
    
    Text* text = new_text();
    
    run_cmds(file->is, text);
    
    save_output(argv[2], text->list);
    
    free_file(file);
    free_text(text);
    
    printf("The program has been executed successfully.\n");
    return 0;
}