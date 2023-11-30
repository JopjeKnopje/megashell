/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:30 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/11/30 16:39:17 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "megashell.h"
#include "builtins.h"
#include "execute.h"
#include "input.h"

bool	execute(t_meta *meta, t_cmd_list *cmds)
{
	t_builtin	is_builtin;
	bool		status;

	is_builtin = BUILTIN_INVALID;
	if ((cmds->content.argv && cmds->content.argv[0]))
		is_builtin = get_builtin(cmds->content.argv[0]);
	if (is_builtin)
		return (run_builtin(is_builtin, meta, &cmds->content));
	else
	{
		status = pipeline_start(meta, cmds);
		signals_setup(MAIN);
		return (status);
	}
	return (false);
}
