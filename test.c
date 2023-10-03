/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:18:36 by ivan-mel          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:04 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
void main()
{
	char str[64];
	
	while (1);
	{
		printf("Please enter a line:\n");
		char *line = NULL;
		size_t len = 0;
		ssize_t lineSize = 0;
		lineSize = getline(&line, &len, stdin);
		printf("You entered %s, which has %zu chars.\n", line, lineSize - 1);
		free(line);
	}
}