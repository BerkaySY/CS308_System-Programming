#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/**
 * @brief Validates the command line arguments
 * @param argc Number of arguments
 * @param argv Array of argument strings
 * @return 1 if arguments are correct (2 arguments, input ends with .dat), 0 otherwise
 */
int check_args(int argc, char** argv)
{
    if (argc != 3) 
    {
        fprintf(stderr, "You have started the program incorrectly. Please start the program with the following format: bin/program data/<input_file> data/<output_file>\n");
        return 0;
    }
    
    char* ext = strstr(argv[1], ".dat");
    if (ext == NULL || strcmp(ext, ".dat") != 0) 
    {
        fprintf(stderr, "The input file format is incorrect. It should have a .dat extension.\n");
        return 0;
    }
    
    return 1;
}

/**
 * @brief Opens a file and initializes a File structure
 * @param filename Name of the file to open
 * @return Pointer to new File structure, or NULL on failure
 */
File* open_file(char* filename)
{
    File* file = (File*)malloc(sizeof(File));
    if (file == NULL) 
    {
        perror("Failed to allocate memory for file");
        return NULL;
    }
    
    file->path = strdup(filename);
    file->is = new_inputstruct(filename);
    
    if (file->is == NULL) 
    {
        perror(filename);
        free(file->path);
        free(file);
        return NULL;
    }
    
    return file;
}

/**
 * @brief Saves the contents of a doubly-linked list to a file, handling special characters
 * @param filename Name of the output file
 * @param list Doubly-linked list containing strings to save
 */
void save_output(char* filename, Dllist list)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) 
    {
        perror(filename);
        return;
    }
    
    Dllist cur = list->flink;
    while (cur != list) 
    {
        if (strstr(cur->val.s, "\\b"))
            fprintf(fp, " ");
        else if (strstr(cur->val.s, "\\n"))
            fprintf(fp, "\n");
        else
            fprintf(fp, "%s", cur->val.s);
        
        cur = cur->flink;
    }
    
    fclose(fp);
}

/**
 * @brief Frees all memory associated with a File structure
 * @param file File structure to free
 */
void free_file(File* file)
{
    if (file != NULL) 
    {
        if (file->is != NULL) 
            jettison_inputstruct(file->is);
            
        free(file->path);
        free(file);
    }
}