/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:30:43 by joppe             #+#    #+#             */
/*   Updated: 2023/11/26 22:31:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void str_free_2d(char **s)
{
	size_t i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*sized_strdup(const char *s, size_t len)
{
	char	*s_d;

	s_d = ft_calloc(sizeof(char), len + 1);
	if (!s_d)
		return (NULL);
	return (ft_memcpy(s_d, s, len));
}

char	**str_arr_append(char **arr, char *s)
{
	char		**tmp;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	len = ft_strlen_2d(arr);
	tmp = ft_calloc(len + 2, sizeof(char *));
	if (!tmp)
	{
		str_free_2d(arr);
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		tmp[i] = arr[i];
		i++;
	}
	tmp[i] = s;
	free(arr);
	return (tmp);
}

int	strlen_largest(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);
	const int	s2_len = ft_strlen(s2);
	const int	comp = s1_len < s2_len;

	return ((comp) * s2_len + (!comp) * s1_len);
}
