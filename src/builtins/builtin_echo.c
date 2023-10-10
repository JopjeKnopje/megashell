/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/10 15:18:43 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

void	print_echo_output(t_cmd_frame *cmd, bool flag)
{
	if (cmd->argv[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (flag)
		return ;
	write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
	write(1, "\n", 1);
}

bool	process_echo_flags(t_cmd_frame *cmd, bool flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		j = 0;
		if (cmd->argv[i][j] == '-')
		{
			j++;
			while (cmd->argv[i][j] && cmd->argv[i][j] == 'n')
			{
				if (cmd->argv[i][j + 1] == '\0')
					flag = true;
				j++;
			}
			if (cmd->argv[i][j] != '\0')
				break ;
			j++;
		}
		i++;
	}
	return (flag);
}

bool	builtin_run_echo(t_meta *meta, t_cmd_frame *cmd)
{
	bool	flag;

	(void) meta;
	flag = false;
	flag = process_echo_flags(cmd, flag);
	print_echo_output(cmd, flag);
	return (true);
}
