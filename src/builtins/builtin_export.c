/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 13:50:29 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printf("%s\n", envp[i]);
		i++;
	}
}

bool	correct_input(char *content)
{
	int	i;

	i = 0;
	if (!ft_isalpha(content[i]) && content[i] != '_')
		return (false);
	while (content[i] && content[i] != '=')
	{
		if (!ft_isalpha(content[i]) || !ft_isalnum(content[i]))
		{
			if (content[i] != '_' && content[i] != '=')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	prepare_variable(char *cmd_start)
{
	int	i;

	i = 0;
	while (cmd_start[i])
	{
		if (cmd_start[i] == '=')
		{
			cmd_start[i] = '\0';
			return (true);
		}
		i++;
	}
	return (false);
}

bool	exists_in_env(char **envp, char *var_value, char *var_name, int len_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len_var) == 0
			&& (envp[i][len_var] == '='))
		{
			free(envp[i]);
			envp[i] = ft_strdup(var_value);
			if (!envp[i])
			{
				printf("Memory allocation error\n");
				return (false);
			}
			return (true);
		}
		i++;
	}
	return (false);
}

int	builtin_run_export(t_meta *meta, t_cmd_frame *cmd)
{
	char	*var_name;
	int		len_var;

	if (!cmd->argv[1])
	{
		print_env(meta->envp);
		return (0);
	}
	var_name = ft_strdup(cmd->argv[1]);
	if (!var_name)
		return (INTERNAL_FAILURE);
	if (!prepare_variable(var_name))
	{
		free(var_name);
		return (INTERNAL_FAILURE);
	}
	len_var = ft_strlen(var_name);
	if (!exists_in_env(meta->envp, cmd->argv[1], var_name, len_var))
		return (handle_export_new_variable(meta, cmd->argv[1], var_name));
	if (!correct_input(var_name))
		return (handle_export_input_errors(var_name));
	handle_export_existing_variable(meta->envp, var_name);
	return (0);
}
