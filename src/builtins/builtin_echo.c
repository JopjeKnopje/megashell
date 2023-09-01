/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:55 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/09/01 20:26:56 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"

void	print_echo_output(t_cmd_list *cmds, bool flag)
{
	printf("%s", cmds->content.argv[1]);
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
	while (cmds->content.argv[i])
	{
		j = 0;
		if (cmds->content.argv[i][0] == '-')
		{
			while (cmds->content.argv[i][j] && cmds->content.argv[i][j] == 'n')
			{
				flag = true;
				j++;
			}
			if (cmds->content.argv[i][j] != '\0')
				break ;
			i++;
		}
		else
			break ;
	}
	return (flag);
}

bool	builtin_run_echo(t_meta *meta, t_cmd_list *cmds)
{
	bool	flag;
	(void)	meta;

	flag = process_echo_flags(cmds);
	print_echo_output(cmds, flag);
	return (true);
}
