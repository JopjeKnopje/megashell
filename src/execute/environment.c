/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:38 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/11/30 20:07:19 by jboeve        ########   odam.nl         */
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

void set_exit_code(int code)
{
	g_exit_code = code;
	printf("g_last_exit [%d]\n", code);
}
