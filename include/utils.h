/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/15 18:32:52 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 23:18:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

// utils_string.c
void	str_free_2d(char **s);
char	**str_arr_append(char **arr, char *s);
char	*sized_strdup(const char *s, size_t len);

#endif
