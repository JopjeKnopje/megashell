/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:11 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/28 18:20:34 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	is_a_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && (str[i] < '0' || str[i] > '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	builtin_run_exit(t_exec *execute, t_cmd_list *cmds)
{
	int	nb;

	if (!cmds->content.argv[1])
		exit(EXIT_SUCCESS);
	nb = ft_atoi(cmds->content.argv[1]);
	if (cmds->content.argv[2])
	{
		if ((is_a_nb(cmds->content.argv[1]) && is_a_nb(cmds->content.argv[2]))
			|| (!is_a_nb(cmds->content.argv[2])))
		{
			printf("exit: too many arguments\n");
			exit(EXIT_FAILURE);
		}
		if (!is_a_nb(cmds->content.argv[1]) && is_a_nb(cmds->content.argv[2]))
		{
			printf("exit: a numeric argument required\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (!is_a_nb(cmds->content.argv[1]))
		printf("Argument isn't a Number\n");
	exit(nb);
}
