/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/06 19:41:31 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

void	print_echo_output(t_cmd_frame *cmd, bool flag)
{
	if (flag == false)
	{
		write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
	}
	write(1, "\n", 1);
}

bool	process_echo_flags(char *cmd)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	printf("cmd[i]: %c\n", cmd[i]);
	if (cmd[i] == '-')
	{
		if (cmd[i] != 'n')
			return (flag);
		i++;
		printf("check\n");
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (flag);
			i++;
		}
		flag = true;
		return (flag);
	}
	else
		return (flag);
}

bool	builtin_run_echo(t_meta *meta, t_cmd_frame *cmd)
{
	bool	flag;

	(void) meta;
	if (cmd->argv[1] == NULL)
	{
		write(1, "\n", 1);
		return (true);
	}
	flag = process_echo_flags(cmd->argv[1]);
	printf("flag: %d\n", flag);
	print_echo_output(cmd, flag);
	return (true);
}
