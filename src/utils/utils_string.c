/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_string.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/15 18:30:43 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/20 23:23:13 by joppe         ########   odam.nl         */
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
	tmp = ft_calloc(len + ft_strlen(s) + 1, sizeof(char *));
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
