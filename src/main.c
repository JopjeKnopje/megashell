/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:00:23 by jboeve            #+#    #+#             */
/*   Updated: 2023/07/25 18:18:11 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>	

// GETENV:
int	main()
{
	char *path = getenv("home");
	printf("getenv: %s\n", path);
}

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
