/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:32:52 by joppe             #+#    #+#             */
/*   Updated: 2023/09/29 13:13:04 by jboeve        ########   odam.nl         */
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

// environment.c
char		**get_environment(char **envp);

#endif
