/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:38 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/29 21:38:16 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include <stdint.h>

char	**get_environment(char **envp)
{
	char	**environment;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	environment = ft_calloc(sizeof(char *), i + 1);
	if (!environment)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		environment[i] = ft_strdup(envp[i]);
		if (!environment[i])
		{
			free_2d(environment);
			return (NULL);
		}
		i++;
	}
	return (environment);
}

char	*envp_find_var(char **envp, char *key)
{
	int		index;
	int 	len;

	index = 0;
	len = ft_strlen(key);
	while (envp[index])
	{
		if (ft_strncmp(envp[index], key, len) == 0)
			return (envp[index] + len);
		index++;
	}
	return (NULL);
}
