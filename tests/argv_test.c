/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   argv_test.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/14 10:20:53 by joppe         #+#    #+#                 */
/*   Updated: 2023/08/14 10:23:57 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
int main(int argc, char *argv[])
{
	int i = 0;

	(void) (argc);

	while (argv[i])
	{
		printf("argv[%d] => [%s]\n", i, argv[i]);
		i++;
	}
	return 0;
}
