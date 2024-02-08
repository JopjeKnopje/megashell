/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:11 by ivan-mel          #+#    #+#             */
/*   Updated: 2024/02/07 16:39:14 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"

bool	is_a_nb(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		if (str[1] != '-' && (str[1] < '0' || str[1] > '9'))
			return (false);
	}
	while (str[i])
	{
		if (str[i] != '-' && (str[i] < '0' || str[i] > '9'))
			return (false);
		i++;
	}
	return (true);
}

int	multiple_args(char *arg1, char *arg2)
{
	printf("exit\n");
	if ((is_a_nb(arg1) && is_a_nb(arg2))
		|| (is_a_nb(arg1) && !is_a_nb(arg2)))
		return (printf("exit: too many arguments\n"), 0);
	if ((!is_a_nb(arg1) && !is_a_nb(arg2)) || \
		(!is_a_nb(arg1) && is_a_nb(arg2)))
	{
		printf("exit: a numeric argument required\n");
		exit(2);
	}
	return (1);
}

int	builtin_run_exit(t_meta *meta, t_cmd_frame *cmd)
{
	int	nb;

	(void) meta;
	if (!cmd->argv[1])
	{
		printf("exit\n");
		exit(g_exit_code);
	}
	nb = ft_atoi(cmd->argv[1]);
	if (cmd->argv[2])
		if (!multiple_args(cmd->argv[1], cmd->argv[2]))
			return (1);
	printf("exit\n");
	if (!is_a_nb(cmd->argv[1]))
	{
		printf("exit %s: a numeric argument required\n", cmd->argv[1]);
		exit(2);
	}
	exit(nb);
}
