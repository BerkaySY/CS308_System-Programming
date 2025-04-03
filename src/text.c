#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

/**
 * @brief Creates and initializes a new Text structure
 * @return Pointer to the new Text structure, or NULL if memory allocation fails
 */
Text* new_text()
{
    Text* text = (Text*)malloc(sizeof(Text));
    if (text == NULL) 
    {
        perror("Failed to allocate memory for text");
        return NULL;
    }
    
    text->list = new_dllist();
    text->cur = text->list;
    
    return text;
}

/**
 * @brief Adds a string to the text at the current position multiple times
 * @param text Text structure to modify
 * @param str String to add (will be copied)
 * @param count Number of times to insert the string
 */
void write(Text* text, char* str, int count) 
{
    if (text == NULL || str == NULL || count < 0) 
    {
        fprintf(stderr, "Invalid arguments in write\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        char* copy = strdup(str);
        if (copy == NULL) 
        {
            perror("Failed to duplicate string");
            return;
        }
        dll_insert_a(text->cur, new_jval_s(copy));
        text->cur = text->cur->flink;
    }
}

/**
 * @brief Deletes up to 'count' occurrences of a string from the current position backward
 * @param text Text structure to modify
 * @param str String to delete
 * @param count Maximum number of occurrences to delete
 */
void del(Text* text, char* str, int count)
{
    int deleted = 0;
    
    while (deleted < count && text->cur != text->list) 
    {
        if (!strcmp(text->cur->val.s, str)) 
        {
            Dllist tmp = text->cur->blink;
            dll_delete_node(text->cur);
            deleted++;
            text->cur = tmp;
        } 
        else 
            text->cur = text->cur->blink;
    }
}

/**
 * @brief Moves the current position to the last node in the text
 * @param text Text structure to modify
 */
void to_end(Text* text)
{
    text->cur = dll_last(text->list);
}

/**
 * @brief Frees all memory associated with a Text structure
 * @param text Text structure to free
 */
void free_text(Text* text)
{
    if (text != NULL) 
    {
        if (text->list != NULL) 
            free_dllist(text->list);
        
        free(text);
    }
}