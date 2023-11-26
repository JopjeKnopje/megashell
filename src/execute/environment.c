/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:38 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/11/26 22:36:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include "plarser.h"
#include <stdio.h>

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

char *env_set_var(char **envp, char *name, char *value)
{
	size_t i = 0;
	size_t len = ft_strlen(name);

	char *tmp;

	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len))
		{
			tmp = ft_strjoin(LAST_EXIT_VAR, value);
			if (!tmp)
				UNIMPLEMENTED("Mem protection");
			free(envp[i]);
			envp[i] = tmp;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
