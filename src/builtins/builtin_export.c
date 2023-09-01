/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                  :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:33:36 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

bool	exists_in_env(char **envp, t_cmd_list *cmds, \
			char *variable, int len_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], variable, len_var) == 0
			&& (envp[i][len_var] == '='))
		{
			free(envp[i]);
			envp[i] = ft_strdup(cmds->content.argv[1]);
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

bool	builtin_run_export(t_meta *meta, t_cmd_list *cmds)
{
	char	*cmd_start;
	char	*variable;
	int		len_var;

	if (!cmds->content.argv[1])
	{
		print_env(meta->envp);
		return (false);
	}
	cmd_start = ft_strdup(cmds->content.argv[1]);
	if (!cmd_start)
		return (false);
	if (!prepare_variable(cmd_start))
		return (false);
	variable = cmd_start;
	len_var = ft_strlen(variable);
	if (exists_in_env(meta->envp, cmds, variable, len_var) == false)
		return (handle_export_new_variable(meta->envp, cmds, cmd_start));
	if (!correct_input(cmd_start))
		return (handle_export_input_errors(cmd_start));
	handle_export_existing_variable(meta->envp, cmd_start);
	return (true);
}
