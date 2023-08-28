/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/28 18:10:13 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

bool	fill_environment(t_exec *execute, char **new_envp, \
			char *cmd_start, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_envp[j] = ft_strdup(execute->envp[j]);
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

bool	add_to_env(t_exec *execute, t_cmd_list *cmds, char *cmd_start)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (execute->envp[i])
		i++;
	new_envp = ft_calloc(sizeof(char *), i + 2);
	if (!new_envp)
	{
		free(cmd_start);
		return (printf("Memory allocation error\n"), false);
	}
	fill_environment(execute, new_envp, cmd_start, i);
	new_envp[i] = ft_strdup(cmds->content.argv[1]);
	if (!new_envp[i])
	{
		free(cmd_start);
		free_2d(new_envp);
		return (printf("Memory allocation error\n"), false);
	}
	free_2d(execute->envp);
	execute->envp = new_envp;
	return (true);
}

bool	handle_export_input_errors(char *cmd_start)
{
	printf("Invalid input\n");
	free(cmd_start);
	return (false);
}

bool	handle_export_existing_variable(t_exec *execute, char *cmd_start)
{
	int	i;

	i = 0;
	while (execute->envp[i])
	{
		printf("envp: %s\n", execute->envp[i]);
		i++;
	}
	free(cmd_start);
	return (true);
}

bool	handle_export_new_variable(t_exec *execute, \
			t_cmd_list *cmds, char *cmd_start)
{
	int	i;

	i = 0;
	if (!correct_input(cmd_start))
	{
		handle_export_input_errors(cmd_start);
		return (true);
	}
	add_to_env(execute, cmds, cmd_start);
	while (execute->envp[i])
	{
		printf("envp: %s\n", execute->envp[i]);
		i++;
	}
	return (true);
}
