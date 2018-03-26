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

typedef void	(*t_f)(void *data);
typedef struct	s_func
{
	int		hex;
	t_f		func;
	int		sleep;
	int		label_size;
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
	unsigned int		index;
	int					pc;
	_Bool				carry;
	int					live;
	int					sleep;
	struct s_process	*next;
	t_f					func;
	int					label_size;
}				t_process;

typedef struct	s_global
{
	long			dump_cycle;
	int				num_of_players;
	t_champ			players[MAX_PLAYERS];
	int				*live;
	_Bool			*taken_index;
	unsigned char	*field;
	t_process		**proc;
	int				period_lives;
	int				cycle_to_die;
	int				checks;
	unsigned char	last_live;
	_Bool			to_visualise;
	int				num_of_processes;
	int				cycle;
	int				total_cycle;
}				t_global;

typedef struct	s_codes
{
	int	t[3];
}				t_codes;

#endif
