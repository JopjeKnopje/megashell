/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/05 10:15:53 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

char	**fill_environment(char **envp, char **new_envp, \
			char *cmd_start, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		if (!new_envp[j])
		{
			free(cmd_start);
			while (j > 0)
			{
				j--;
				free(new_envp[j]);
			}
			free(new_envp);
			return (new_envp);
		}
		j++;
	}
	return (new_envp);
}

char	**add_to_env(char **envp, char *arg, char *cmd_start)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	new_envp = ft_calloc(sizeof(char *), i + 2);
	if (!new_envp)
	{
		free(cmd_start);
		printf("Memory allocation error\n");
		return (NULL);
	}
	new_envp = fill_environment(envp, new_envp, cmd_start, i);
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
	{
		free(cmd_start);
		free_2d(new_envp);
		printf("Memory allocation error\n");
		return (NULL);
	}
	free_2d(envp);
	envp = new_envp;
	return (envp);
}

bool	handle_export_input_errors(char *cmd_start)
{
	printf("Invalid input\n");
	free(cmd_start);
	return (false);
}

bool	handle_export_existing_variable(char **envp, char *cmd_start)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n",envp[i]);
		i++;
	}
	free(cmd_start);
	return (true);
}

bool	handle_export_new_variable(t_meta *meta, char *arg, char *cmd_start)
{
	int	i;

	i = 0;
	if (!correct_input(cmd_start))
	{
		handle_export_input_errors(cmd_start);
		return (true);
	}
	meta->envp = add_to_env(meta->envp, arg, cmd_start);
	return (true);
}
