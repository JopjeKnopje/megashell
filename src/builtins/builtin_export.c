/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/22 17:58:54 by ivan-mel         ###   ########.fr       */
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
			if (content[i] != '_')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	builtin_run_export(t_exec *execute, t_cmd_list *cmds)
{
	int		i;
	int		len_var;
	char	*variable;
	char	*cmd_start;
	bool	exist;

	i = 0;
	exist = true;
	cmd_start = NULL;
	if (!cmds->content.argv[1])
	{
		print_env(execute);
		return (true);
	}
	while (cmds->content.argv[1][i])
	{
		if (correct_input(cmds->content.argv[1][i]) == false)
		{
			printf("Doesn't exist\n");
			exist = false;
		}
		if (cmds->content.argv[1][i] == '=' && exist == true)
		{
			exists_in_path();
			break ;
		}
		cmd_start = cmds->content.argv[1];
		printf("cmds->content.argv: %c\n", cmds->content.argv[1][i]);
		i++;
	}
	if (cmds->content.argv[1][i] == '=')
		cmd_start[i] = '\0';
	printf("cmds_start: %s\n", cmd_start);
	variable = cmds->content.argv[1];
	len_var = ft_strlen(variable);
	while (execute->envp[i])
	{
		if (ft_strncmp(execute->envp[i], variable, len_var) == 0
			&& (execute->envp[i][len_var] == '='))
		{
			printf("Comparing '%s' with '%s'\n", execute->envp[i], variable);
			while (execute->envp[i] != NULL)
				i++;
			ft_memcpy(execute->envp[i + 1], variable, len_var);
			printf("%s\n", execute->envp[i]);
		}
	}
	return true;
}
