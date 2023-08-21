/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/15 18:38:03 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	print_echo_output(t_cmd_list *cmds, bool flag)
{
	printf("%s", cmds->action[1]);
	if (!flag)
		printf("\n");
}

bool	process_echo_flags(t_cmd_list *cmds)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	j = 0;
	flag = false;
	while (cmds->action[i])
	{
		j = 0;
		if (cmds->action[i][0] == '-')
		{
			while (cmds->action[i][j] && cmds->action[i][j] == 'n')
			{
				flag = true;
				j++;
			}
			if (cmds->action[i][j] != '\0')
				break ;
			i++;
		}
		else
			break ;
	}
	return (flag);
}

bool	builtin_run_echo(t_exec *execute, t_cmd_list *cmds)
{
	bool	flag;

	flag = process_echo_flags(cmds);
	print_echo_output(cmds, flag);
	return (true);
}
