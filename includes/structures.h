/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:18 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:18 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "op.h"
# define NUM_OF_FUNCS 1

typedef void	(*t_f)(void *data);
typedef struct	s_func
{
	int		hex;
	t_f		func;
	int		sleep;
}				t_func;

typedef struct	s_champ
{
	int				index;
	char			*filename;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	field[CHAMP_MAX_SIZE];
	int				field_size;
	int				startpos;
}				t_champ;

typedef struct	s_process
{
	int					index;
	unsigned int		*registry;
	int					pc;
	_Bool				carry;
	int					live;
	int					sleep;
	struct s_process	*next;
	t_f					func;
}				t_process;

#endif
