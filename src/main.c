/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/07/24 12:00:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/07/26 12:14:17 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <signal.h>
#include <sys/ttycom.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>



const int FD = STDOUT_FILENO;


void print_winsize(struct winsize *size)
{
	printf("ws_row %d | ws_col %d | ws_xpixel %d | ws_ypixel %d\n", size->ws_row, size->ws_col, size->ws_xpixel, size->ws_ypixel);
}

void error_exit()
{
	perror(strerror(errno));
	exit(1);
}

void resize_tty_window()
{
	struct winsize size;

	if (ioctl(FD, TIOCGWINSZ, &size) == -1)
		error_exit();
	print_winsize(&size);

	size.ws_ypixel = 2812;
	size.ws_xpixel = 2620;
	size.ws_row = 10;
	size.ws_col = 10;

	if (ioctl(FD, TIOCSWINSZ, &size) == -1)
		error_exit();

	if (ioctl(FD, TIOCGWINSZ, &size) == -1)
		error_exit();
	print_winsize(&size);
}

int main(int argc, char *argv[])
{
	int istty = isatty(FD);
	if (!istty)
		error_exit();
	printf("isatty: %d\n", istty);

	const char *name = ttyname(FD);
	if (!name)
		error_exit();
	printf("ttyname: [%s]\n", name);


	resize_tty_window();





	return (0);
}
