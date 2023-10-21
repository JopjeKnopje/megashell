/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:32:52 by joppe             #+#    #+#             */
/*   Updated: 2023/10/10 17:03:47 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

// utils_string.c
void	str_free_2d(char **s);
char	**str_arr_append(char **arr, char *s);
char	*sized_strdup(const char *s, size_t len);
int		strlen_largest(const char *s1, const char *s2);
char	**search_in_path(char **envp, char *cmd);

#endif
