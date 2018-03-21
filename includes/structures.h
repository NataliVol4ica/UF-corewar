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
# define NUM_OF_FUNCS 2

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
	char			*name;
	char			*comment;
	unsigned char	*field;
	int				field_size;
	int				startpos;
}				t_champ;

typedef struct	s_process
{
	unsigned int		*registry;
	int					pc;
	_Bool				carry;
	int					live;
	int					sleep;
	struct s_process	*next;
	t_f					func;
}				t_process;

typedef struct	s_global
{
	long			dump_cycle;
	int				num_of_players;
	t_champ			players[MAX_PLAYERS];
	_Bool			*taken_index;
	unsigned char	*field;
	t_process		**proc;
	int				period_lives;
	int				cycle_to_die;
	int				checks;
}				t_global;

#endif
