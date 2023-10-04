/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/04 02:25:37 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"
#include "megashell.h"
#include "utils.h"

t_builtin	get_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, BUILTINS_NAME[i],
				strlen_largest(BUILTINS_NAME[i], cmd)) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_INVALID);
}

bool	run_builtin(t_builtin builtin, t_meta *meta, t_cmd_list *cmds)
{
	bool	(*BUILTINS_FUNCTS[BUILTIN_COUNT]) (t_meta *a, t_cmd_list *cmds) = {
	builtin_run_pwd,
	builtin_run_env,
	builtin_run_echo,
	builtin_run_cd,
	builtin_run_export,
	builtin_run_unset,
	builtin_run_exit,};

	return (*BUILTINS_FUNCTS[builtin - 1])(meta, cmds);
}
