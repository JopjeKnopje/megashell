/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:11 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/22 14:41:43 by ivan-mel         ###   ########.fr       */
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

// exit dan exit errorcode vorige
	if (!cmds->content.argv[1])
		exit(EXIT_SUCCESS);
	nb = ft_atoi(cmds->content.argv[1]);
// unless multiple digits with spaces
	if (cmds->content.argv[2])
		printf("Too Many Arguments\n");
	else if (!is_a_nb(cmds->content.argv[1]))
		printf("Argument isn't a Number\n");
	exit(nb);
}
