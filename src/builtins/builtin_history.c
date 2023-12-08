/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_history.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/02 20:20:16 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/08 18:08:04 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "megashell.h"
#include "plarser.h"
#include <readline/history.h>

int	builtin_run_history(t_meta *meta, t_cmd_frame *cmd)
{
	HIST_ENTRY	**const hist = history_list();
	size_t		i;

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
