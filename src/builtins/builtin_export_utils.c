/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:32:52 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

bool	fill_environment(char **envp, char **new_envp, \
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
			return (false);
		}
		j++;
	}
	return (true);
}

bool	add_to_env(char **envp, t_cmd_list *cmds, char *cmd_start)
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
		return (printf("Memory allocation error\n"), false);
	}
	fill_environment(envp, new_envp, cmd_start, i);
	new_envp[i] = ft_strdup(cmds->content.argv[1]);
	if (!new_envp[i])
	{
		free(cmd_start);
		free_2d(new_envp);
		return (printf("Memory allocation error\n"), false);
	}
	free_2d(envp);
	envp = new_envp;
	return (true);
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
		printf("envp: %s\n",envp[i]);
		i++;
	}
	free(cmd_start);
	return (true);
}

bool	handle_export_new_variable(char **envp, \
			t_cmd_list *cmds, char *cmd_start)
{
	int	i;

	i = 0;
	if (!correct_input(cmd_start))
	{
		handle_export_input_errors(cmd_start);
		return (true);
	}
	add_to_env(envp, cmds, cmd_start);
	while (envp[i])
	{
		printf("envp: %s\n", envp[i]);
		i++;
	}
	return (true);
}
