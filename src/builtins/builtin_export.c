/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:03 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/22 13:22:46 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_export(t_exec *execute, t_cmd_list *cmds)
{
	int		i;
	int		len_var;
	char	*variable;

	i = 0;
	len_var = ft_strlen(variable);
	if (!cmds->action[1])
		return (false);
	variable = cmds->action[1];
	while (execute->envp[i])
	{
		if (ft_strncmp(execute->envp[i], variable, len_var) == 0
			&& (execute->envp[i][len_var] == '='))
		{
			printf("Comparing '%s' with '%s'\n", execute->envp[i], variable);
			while (execute->envp[i] != NULL)
				i++;
			ft_strjoin();
		}
	}
}
