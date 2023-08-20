/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 18:06:33 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 18:50:00 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include <unistd.h>
#include "plarser.h"

void	print_bits(size_t const size, void const * const ptr);
void	print_2d_arr(char **s, char *name);
void	print_cf_list(t_cmd_list *list);
void	print_token(t_token t);
void	print_tokens(t_tok_list *lst);
void	print_cmds(t_cmd_list *cmds);

#endif 
