/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:38 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/29 13:25:57 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

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

char *envp_find_var(char **envp, char *s, int len)
{
	while (*envp) 
	{
		if (!ft_strncmp(*envp, s, len))
			return (*envp);
		envp++;
	}
	return (NULL);
}
