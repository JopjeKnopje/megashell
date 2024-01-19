/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:58:16 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/19 14:17:39 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"
#include "megashell.h"

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
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = ft_calloc(sizeof(char *), i + 2);
	if (!new_envp)
	{
		free(cmd_start);
		return (print_error("Memory allocation error\n"), NULL);
	}
	new_envp = fill_environment(envp, new_envp, cmd_start, i);
	free(cmd_start);
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
	{
		free_2d(new_envp);
		return (print_error("Memory allocation error\n"), NULL);
	}
	free_2d(envp);
	envp = new_envp;
	return (envp);
}

bool	handle_export_input_errors(char *cmd_start)
{
	print_error("Invalid input");
	free(cmd_start);
	return (false);
}

bool	handle_export_existing_variable(char **envp, char *cmd_start)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	free(cmd_start);
	return (true);
}

int	handle_export_new_variable(t_meta *meta, char *arg, char *cmd_start)
{
	if (!correct_input(cmd_start))
	{
		handle_export_input_errors(cmd_start);
		return (0);
	}
	meta->envp = add_to_env(meta->envp, arg, cmd_start);
	if (!meta->envp)
		return (INTERNAL_FAILURE);
	return (0);
}
