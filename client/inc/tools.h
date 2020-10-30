/*
** EPITECH PROJECT, 2019
** tools
** File description:
** tools
*/

#ifndef __MYTEAMS_TOOLS_H__
#define __MYTEAMS_TOOLS_H__

#include "client_header.h"

/* Convert: */

    /* \number = number to convert to a string. */
string_t int_to_string(int number);

/* Memory: */

    /* \size = new size for realloc */
    /* \last = the string where we must copy the content */
string_t my_realloc(unsigned int size, string_t *last);

/*Split array: */
    /* \str = the str to split. */
    /* \delimiter = the delimiter for the split. */
array split(struct string_s str, struct string_s delimiter);

#endif //__MYTEAMS_TOOLS_H__
