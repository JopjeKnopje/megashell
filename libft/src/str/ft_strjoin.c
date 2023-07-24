/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 19:59:09 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/03 15:36:43 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	total_size;

	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	buf = (char *) malloc(total_size);
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, s1, ft_strlen(s1) + 1);
	ft_strlcat(buf, s2, total_size);
	return (buf);
}
