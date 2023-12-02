/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_history.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/02 20:20:16 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/02 20:28:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "plarser.h"
#include <readline/history.h>
#include <stdio.h>

int	builtin_run_history(t_meta *meta, t_cmd_frame *cmd)
{
	HIST_ENTRY	**hist;
	size_t		i;

	i = 0;
	hist = history_list();
	if (!hist)
		return (1);
	while (hist[i])
	{
		if (hist[i]->line)
			printf("%ld %s\n", i, hist[i]->line);
		i++;
	}
	return (0);
}
