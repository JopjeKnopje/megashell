/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:21:44 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/12/11 16:23:31 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include <readline/history.h>

int	builtin_run_history(t_meta *meta, t_cmd_frame *cmd)
{
	HIST_ENTRY **const	hist = history_list();
	size_t				i;

	(void) meta;
	(void) cmd;
	i = 0;
	if (!hist)
		return (INTERNAL_FAILURE);
	while (hist[i])
	{
		if (hist[i]->line)
			printf("%ld %s\n", i, hist[i]->line);
		i++;
	}
	return (0);
}
