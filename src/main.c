/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:33:28 by jboeve            #+#    #+#             */
/*   Updated: 2023/12/08 23:33:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "megashell.h"
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUILD_TEST

// void find_offset()
// {
// 	void	*base 		= &rl_on_new_line;
// 	void	*target		= &rl_set_prompt;
// 	uint32_t offset;
//
// 	printf("target	= \t[%p]\n", target);
// 	printf("base	= \t[%p]\n", base);
//
// 	if (target > base)
// 		printf("target bigger\n");
// 	offset = base - target;
//
// 	printf("offset = [%x]\n", offset);
// }

int main(int argc, char *argv[], char *envp[])
{
	// find_offset();
	return megashell(argc, argv, envp);
}


#endif
