/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 13:38:44 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "builtins.h"
#include "execute.h"
#include "input.h"
#include "plarser.h"
#include <stdio.h>

static size_t	count_cmds(t_cmd_list *cmds)
{
	size_t	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}

int	execute(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;
	int			status;

	status = 0;
	is_builtin = BUILTIN_INVALID;
	if (count_cmds(cmds) == 1 && cmds->content.argv && cmds->content.argv[0])
		is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin)
		status = run_builtin(is_builtin, meta, &cmds->content);
	else
		status = pipeline_start(meta, cmds);
	return (status);
}
