/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/05 12:42:28 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

void	print_echo_output(t_cmd_frame *cmd, bool flag)
{
	if (!flag)
	{
		printf("\n");
		return;
	}
	printf("%s", cmd->argv[1]);
}

bool	process_echo_flags(t_cmd_frame *cmd)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	j = 0;
	flag = false;
	while (cmd->argv[i])
	{
		j = 0;
		if (cmd->argv[i][0] == '-')
		{
			while (cmd->argv[i][j] && cmd->argv[i][j] == 'n')
			{
				flag = true;
				j++;
			}
			if (cmd->argv[i][j] != '\0')
				break ;
			i++;
		}
		else
			break ;
	}
	return (flag);
}

bool	builtin_run_echo(t_meta *meta, t_cmd_frame *cmd)
{
	bool	flag;
	(void)	meta;

	flag = process_echo_flags(cmd);
	print_echo_output(cmd, flag);
	return (true);
}
