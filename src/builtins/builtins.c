/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:03:10 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/15 15:26:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"

static int	largest_input(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);
	const int	s2_len = ft_strlen(s2);
	const int	comp = s1_len < s2_len;

	return ((comp) * s2_len + (!comp) * s1_len);
}

t_builtin	get_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, BUILTINS_NAME[i],
				largest_input(BUILTINS_NAME[i], cmd)) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_INVALID);
}

void	run_builtin(t_builtin builtin, t_exec *execute, t_cmd_list *cmds)
{
	bool	(*BUILTINS_FUNCTS[BUILTIN_COUNT]) (t_exec *a, t_cmd_list *cmds) = {
	builtin_run_pwd,
	builtin_run_env,
	builtin_run_echo,
	builtin_run_cd,
	builtin_run_export,
	builtin_run_unset,
	builtin_run_exit,};

	(*BUILTINS_FUNCTS[builtin - 1])(execute, cmds);
}
