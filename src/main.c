/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/08/22 13:33:28 by jboeve        #+#    #+#                 */
/*   Updated: 2023/08/22 13:33:37 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// #include "execute.h"
// void	use_list(char **argv, int argc, char **envp)
// {
// 	t_exec		execute;
// 	t_cmd_list	*list;
//
// 	list = mock_input();
// 	search_path(&execute, envp);
// 	execution(&execute, list);
// }
//
// int	main(int argc, char **argv, char **envp)
// {
// 	use_list(argv, argc, envp);
// 	return (0);
// }

#include "megashell.h"

int main(int argc, char *argv[], char *envp[])
{
	return megashell(argc, argv, envp);
}
