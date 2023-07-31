/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:38 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/07/31 18:11:22 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"


char **get_environment(char **envp)
{
	char	**environment;
	int		i;

	i = 0;
	while (envp[i])
	{
		printf("i: %d\n", i);
		printf("envp: %s\n", envp[i]);
		i++;
	}
	environment = ft_calloc(sizeof(char *), i + 1);
	if (!environment)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		environment[i] = ft_strdup(envp[i]);
		printf("environment: %s\n", environment[i]);
		i++;
	}
	return (environment);
}
