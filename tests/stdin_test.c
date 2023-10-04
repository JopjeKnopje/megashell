/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   stdin_test.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/03 14:43:16 by jboeve        #+#    #+#                 */
/*   Updated: 2023/10/03 14:52:06 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>

#define BUFFER_SIZE 64
#define OPEN_MAX 1024

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strdup(const char *s)
{
	int		i;
	int		len;
	char	*buffer;

	len = gnl_strlen((char *) s);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = s[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*s_sub;

	i = 0;
	if (!s)
		return (NULL);
	s_len = gnl_strlen((char *) s);
	if (start > s_len)
		return (gnl_strdup(""));
	s_len -= start;
	if (len > s_len)
		len = s_len;
	s_sub = malloc(sizeof(char) * (len + 1));
	if (!s_sub)
		return (NULL);
	while (i < len)
	{
		s_sub[i] = s[start + i];
		i++;
	}
	s_sub[i] = 0;
	return (s_sub);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = gnl_strlen((char *) s) + 1;
	i = 0;
	while (i < len)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}


char	*gnl_strjoin_free(char *s_base, char *s_append)
{
	int		i;
	int		len_base;
	int		len_append;
	char	*s_new;

	len_base = gnl_strlen(s_base);
	len_append = gnl_strlen(s_append);
	s_new = malloc(len_base + len_append + 1);
	if (!s_new)
		return (free(s_base), (NULL));
	i = 0;
	while (s_base[i])
	{
		s_new[i] = s_base[i];
		i++;
	}
	i = 0;
	while (s_append[i])
	{
		s_new[len_base + i] = s_append[i];
		i++;
	}
	free(s_base);
	s_new[len_base + len_append] = 0;
	return (s_new);
}

static	char	*next(char **file_content)
{
	char	*end;
	char	*line;
	char	*file_content_new;
	int		line_len;

	if (!*file_content)
		return (NULL);
	end = gnl_strchr(*file_content, '\n') + 1;
	if (!end)
		end = *file_content + (gnl_strlen(*file_content) * sizeof(char));
	line_len = end - *file_content;
	line = gnl_substr(*file_content, 0, line_len);
	if (!line)
		return (NULL);
	file_content_new = gnl_substr(*file_content, line_len,
			gnl_strlen(*file_content) - line_len);
	if (!file_content_new)
		return (free(line), NULL);
	free(*file_content);
	*file_content = file_content_new;
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

static	char	*read_file(char *file_content, int fd)
{
	int		r;
	char	read_buf[BUFFER_SIZE + 1];

	r = 1;
	read_buf[BUFFER_SIZE] = 0;
	while (r)
	{
		r = read(fd, read_buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(file_content);
			return (NULL);
		}
		if (r == 0)
			return (file_content);
		if (r < BUFFER_SIZE)
			read_buf[r] = 0;
		file_content = gnl_strjoin_free(file_content, read_buf);
		if (!file_content)
			return (NULL);
		if (gnl_strchr(read_buf, '\n'))
			break ;
	}
	return (file_content);
}

char	*get_next_line(int fd)
{
	static char	*file_content[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!file_content[fd])
		file_content[fd] = gnl_strdup("");
	if (!file_content[fd])
		return (NULL);
	file_content[fd] = read_file(file_content[fd], fd);
	if (!file_content[fd])
		return (NULL);
	line = next(&file_content[fd]);
	if (!line)
	{
		free(file_content[fd]);
		file_content[fd] = NULL;
		return (NULL);
	}
	return (line);
}


int main()
{
	char *line = get_next_line(STDIN_FILENO);

	while (line)
	{
		dprintf(STDERR_FILENO, "[%s]\n", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return 0;
}
