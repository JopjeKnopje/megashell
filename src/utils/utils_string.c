/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils_string.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/15 18:30:43 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/15 18:49:21 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void str_free_2d(char **s)
{
	size_t i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
