/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/01/16 14:44:08 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

static void	print_echo_output(t_cmd_frame *cmd, int i)
{
	while (cmd->argv && cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
}

static bool	process_echo_flags(t_cmd_frame *cmd, bool flag)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (cmd->argv[i][0] == '-' && cmd->argv[i][1] == '\0')
		write (1, "-\n", 2);
	while (cmd->argv[i] && cmd->argv[i][0] == '-')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] == '\0')
			flag = false;
		else
			break ;
		i++;
	}
	print_echo_output(cmd, i);
	return (flag);
}

int	builtin_run_echo(t_meta *meta, t_cmd_frame *cmd)
{
	int	flag;

	(void) meta;
	flag = true;
	if (!cmd->argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = process_echo_flags(cmd, flag);
	if (flag)
		write(1, "\n", 1);
	return (0);
}
