/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 18:06:33 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/16 12:35:24 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include <unistd.h>
#include "plarser.h"

void	print_bits(size_t const size, void const * const ptr);
void	print_2d_arr(char **s, char *name);
void	print_cf_list(t_cf_list *list);
void	print_tokens(t_tok_list *lst);

#endif 
