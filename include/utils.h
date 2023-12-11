/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:32:52 by joppe             #+#    #+#             */
/*   Updated: 2023/12/08 16:13:38 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

// utils_string.c
void	str_free_2d(char **s);
char	**str_arr_append(char **arr, char *s);
char	*sized_strjoin(char const *s1, size_t l1, char const *s2, size_t l2);
char	*sized_strdup(const char *s, size_t len);
int		strlen_largest(const char *s1, const char *s2);
char	**search_in_path(char **envp, char *cmd);

// utils_math.c
int ft_abs(int x);

#endif
