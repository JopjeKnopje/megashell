/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:00:23 by jboeve            #+#    #+#             */
/*   Updated: 2023/08/05 01:10:22 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <dirent.h>
// #include <stdlib.h>
// #include <limits.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <readline/readline.h>
// #include <readline/history.h>	

#include "../execute.h"

// instead of error with 2 check builtins

void	initialization(t_exec *execute, char **argv, int argc)
{
	execute->argv = &argv[1];
	execute->argc = argc - 1;
}

void	use_list(char **argv, int argc, char **envp)
{
	t_exec	execute;
	t_cmds	*list;

	list = mock_input();
	initialization(&execute, argv, argc);
	// printf("list: %s\n", list->action[0]);
	search_path(&execute, list);
	// execute(&execute, pipes);
	
}

int	main(int argc, char **argv, char **envp)
{
	use_list(argv, argc, envp);
	return (0);
}

// GETENV:
// int	main()
// {
// 	char *path = getenv("home`");
// 	printf("getenv: %s\n", path);
// }

// OPENDIR & CLOSEDIR:

// int main()
// {
//     DIR *dir;

//     dir = opendir("libft");
//     if (dir == NULL) {
//         printf("Couldn't open dir\n");
//     } else {
//         printf("Opened dir\n");
//     }

//     if (dir != NULL)
//         closedir(dir);
// }

// STAT:

// int	main()
// {
// 	char *txt = "text.txt";
// 	struct stat buf;
// 	int stats = stat(txt, &buf);
// 	printf("Information: %d\n", stats);
// 	printf("Information: %lld\n", buf.st_size);
// }

// CHRDIR:

// int main()
// {
// 	int f = fork();
// 	char cwd[PATH_MAX];
// 	if (f == 0)
// 	{
// 		chdir("/Users/ivan-mel/Documents/Projects");
// 		getcwd(cwd, sizeof(cwd));
// 		printf("Current working dir: %s\n", cwd);
// 	}
// 	getcwd(cwd, sizeof(cwd));
// 	printf("Current working dir: %s\n", cwd);
//     return 0;
// }

// GETCWD:

// int main() {
//    char cwd[PATH_MAX]; /* PATH_MAX: limit for the lenght of file name */
//    if (getcwd(cwd, sizeof(cwd)) != NULL) {
//        printf("Current working dir: %s\n", cwd);
//    } else {
//        perror("getcwd() error");
//        return 1;
//    }
//    return 0;
// }
