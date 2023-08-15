/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 18:05:42 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 18:49:54 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "test_utils.h"
#include <stdio.h>

void print_bits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


