/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:11 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 15:22:01 by jboeve        ########   odam.nl         */
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
		{
			printf("exit %c: numeric argument required\n", str[0]);
			return (false);
		}
	}
	while (str[i])
	{
		if (str[i] != '-' && (str[i] < '0' || str[i] > '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	builtin_run_exit(t_meta *meta, t_cmd_frame *cmd)
{
	int	nb;

	(void) meta;

	if (!cmd->argv[1])
		exit(EXIT_SUCCESS);
	nb = ft_atoi(cmd->argv[1]);
	if (cmd->argv[2])
	{
		if ((is_a_nb(cmd->argv[1]) && is_a_nb(cmd->argv[2]))
			|| (!is_a_nb(cmd->argv[2])))
		{
			printf("exit: too many arguments\n");
			exit(EXIT_FAILURE);
		}
		if (!is_a_nb(cmd->argv[1]) && is_a_nb(cmd->argv[2]))
		{
			printf("exit: a numeric argument required\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (!is_a_nb(cmd->argv[1]))
		printf("exit %s: a numeric argument required\n", cmd->argv[1]);
	exit(nb);
}
