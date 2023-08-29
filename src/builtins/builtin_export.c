/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/28 17:48:31 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	print_env(t_exec *execute)
{
	int	i;

	i = 0;
	while (execute->envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printf("%s\n", execute->envp[i]);
		i++;
	}
}

bool	correct_input(char *content)
{
	int	i;

	i= 0;
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
			cmd_start[i] = '\0'; // Null-terminate at '='
			return (true);
		}
		i++;
	}
	return (false);
}

bool	exists_in_env(t_exec *execute, t_cmd_list *cmds, \
			char *variable, int len_var)
{
	int	i;

	i = 0;
	while (execute->envp[i])
	{
		if (ft_strncmp(execute->envp[i], variable, len_var) == 0
			&& (execute->envp[i][len_var] == '='))
		{
			free(execute->envp[i]);
			execute->envp[i] = ft_strdup(cmds->content.argv[1]);
			if (!execute->envp[i]) 
			{
				printf("Memory allocation error\n");
				return (false);
			}
			return (true);
			break ;
		}
		i++;
	}
	return (false);
}

bool	builtin_run_export(t_exec *execute, t_cmd_list *cmds)
{
	char	*cmd_start;
	char	*variable;
	int		len_var;

	if (!cmds->content.argv[1])
	{
		print_env(execute);
		return (false);
	}
	cmd_start = ft_strdup(cmds->content.argv[1]);
	if (!cmd_start)
		return (false);
	if (!prepare_variable(cmd_start))
		return (false);
	variable = cmd_start;
	len_var = ft_strlen(variable);
	if (exists_in_env(execute, cmds, variable, len_var) == false)
		return (handle_export_new_variable(execute, cmds, cmd_start));
	if (!correct_input(cmd_start))
		return (handle_export_input_errors(cmd_start));
	handle_export_existing_variable(execute, cmd_start);
	return (true);
}
