/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:00:23 by jboeve            #+#    #+#             */
/*   Updated: 2023/08/14 17:51:41 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// instead of error with 2 check builtins

void	use_list(char **argv, int argc, char **envp)
{
	t_exec		execute;
	t_cmd_list	*list;

	list = mock_input();
	search_path(&execute, envp);
	execution(&execute, list);
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
