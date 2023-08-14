/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:08:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/08/14 16:22:29 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	builtin_run_env(t_exec *execute)
{
	int	i;

	i = 0;
	while (execute->envp[i])
	{
		printf("%s\n", execute->envp[i]);
		i++;
	}
}
