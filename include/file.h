#ifndef FILE_H
#define FILE_H

#include "fields.h"
#include "dllist.h"

/**
 * @brief Structure representing a file with its input stream and path
 */
typedef struct {
    IS is;      /**< Input stream structure for reading the file */
    char* path; /**< Path to the file */
} File;


int check_args(int argc, char **argv);
File* open_file(char* filename);
void save_output(char* filename, Dllist list);
void free_file(File* file);

#endif