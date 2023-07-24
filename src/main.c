/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:00:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/24 14:49:38 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char *argv[])
{
	printf("fakka megashell\n");
	printf("%d\n", rl_readline_version);
	
	return 0;
}
