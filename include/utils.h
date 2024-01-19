/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:32:52 by joppe             #+#    #+#             */
/*   Updated: 2024/01/19 16:09:28 by ivan-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "plarser.h"
# include <unistd.h>

// utils_string.c
void	str_free_2d(char **s);
char	**str_arr_append(char **arr, char *s);
char	*sized_strjoin(char const *s1, size_t l1, char const *s2, size_t l2);
char	*sized_strdup(const char *s, size_t len);
int		strlen_largest(const char *s1, const char *s2);
char	**search_in_env(char **envp, char *cmd);

bool	lx_is_redir_heredoc(char *s, t_token_kind k);

#endif
