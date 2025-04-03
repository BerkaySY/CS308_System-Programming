#ifndef TEXT_H
#define TEXT_H

#include "dllist.h"

/**
 * @brief Structure representing text data with a doubly-linked list and current position
 */
typedef struct {
    Dllist list;    /**< Doubly-linked list containing text elements */
    Dllist cur;     /**< Current position in the text */
} Text;


Text* new_text();
void write(Text* text, char* str, int count);
void del(Text* text, char* str, int count);
void to_end(Text* text);
void free_text(Text* text);

#endif