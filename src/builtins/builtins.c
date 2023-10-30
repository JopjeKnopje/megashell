/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/31 00:33:46 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include "utils.h"
#include <stdio.h>

typedef bool	(*t_builtin_func)(t_meta *meta, t_cmd_frame *cmd);

static const char *BUILTINS_NAME[BUILTIN_COUNT] = {
	"INVALID",
	"pwd",
	"env",
	"echo",
	"cd",
	"export",
	"unset",
	"exit",
};

t_builtin	get_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (BUILTIN_INVALID);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, BUILTINS_NAME[i], \
		strlen_largest(BUILTINS_NAME[i], cmd)) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_INVALID);
}

bool	run_builtin(t_builtin builtin, t_meta *meta, t_cmd_frame *cmd)
{
	const t_builtin_func	funcs[] = {
		NULL, \
		builtin_run_pwd, \
		builtin_run_env, \
		builtin_run_echo, \
		builtin_run_cd, \
		builtin_run_export, \
		builtin_run_unset, \
		builtin_run_exit, \
	};

	return ((*funcs[builtin])(meta, cmd));
}
