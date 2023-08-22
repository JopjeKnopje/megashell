/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/22 14:41:56 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	print_env(t_exec *execute)
{
	int	i;

	i = 0;
	printf("test\n");
	while (execute->envp[i])
	{
		ft_putstr_fd("declare -x", STDOUT_FILENO);
		printf("%s\n", execute->envp[i]);
		i++;
	}
}

bool	builtin_run_export(t_exec *execute, t_cmd_list *cmds)
{
	int		i;
	int		len_var;
	char	*variable;

	i = 0;
	if (!cmds->content.argv[1])
		print_env(execute);
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
			// ft_strjoin();
		}
	}
	return true;
}
