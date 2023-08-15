/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/15 17:11:40 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_echo(t_exec *execute, t_cmd_list *cmds)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
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
	while (cmds->action[i])
	{
		printf("%s\n", cmds->action[i]);
		i++;
	}
	if (flag = true)
		printf("\n");
	return (true);
}
