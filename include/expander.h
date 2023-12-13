/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   expander.h                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/12 18:45:58 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/13 00:41:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
#include "plarser.h"

typedef struct s_exp {
	char	**envp;
	char	*s_exp;
	char	*end;
	size_t  step;
	size_t  i;
	t_token *t;
} t_exp;


// expander_utils.c
t_exp ex_pack_struct(t_token *t, char **envp);
bool ex_iterate(t_exp *exp);

// expander.c
size_t	ex_var_len(char *s);
char	*ex_str_append(char *s_base, char *s_append, size_t append_size);
char *expand_var(char **envp, t_token *t, size_t i);


#endif
