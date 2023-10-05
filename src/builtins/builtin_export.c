/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/05 02:18:14 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printf("%s\n",envp[i]);
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

bool	exists_in_env(char **envp, char *arg, char *variable, int len_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], variable, len_var) == 0
			&& (envp[i][len_var] == '='))
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			if (!envp[i]) 
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

bool	builtin_run_export(t_meta *meta, t_cmd_frame *cmd)
{
	char	*cmd_start;
	char	*variable;
	int		len_var;

	if (!cmd->argv[1])
	{
		print_env(meta->envp);
		return (false);
	}
	cmd_start = ft_strdup(cmd->argv[1]);
	if (!cmd_start)
		return (false);
	if (!prepare_variable(cmd_start))
		return (false);
	variable = cmd_start;
	len_var = ft_strlen(variable);
	printf("cmd->argv[1]: %s\n", cmd->argv[1]);
	printf("variable: %s\n", variable);
	printf("cmd_start: %s\n", cmd_start);
	if (exists_in_env(meta->envp, cmd->argv[1], variable, len_var) == false)
		return (handle_export_new_variable(meta, cmd->argv[1], cmd_start));
	if (!correct_input(cmd_start))
		return (handle_export_input_errors(cmd_start));
	printf("cmd->argv[1]: %s\n", cmd->argv[1]);
	printf("variable: %s\n", variable);
	printf("cmd_start: %s\n", cmd_start);
	handle_export_existing_variable(meta->envp, cmd_start);
	return (true);
}
