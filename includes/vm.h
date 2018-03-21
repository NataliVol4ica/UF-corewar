/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:37:08 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:37:12 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# define MALL(x) if (!(x)) mall_error()

//# include <ncurses.h>
# include "structures.h"
# include "proc.h"
# include "encurse.h"
//# include <ncurses.h>


void	init_globals(void);

/*
** INPUT READING
*/

void	parse_player(char *name, t_champ *player);
_Bool	parse_n_flag(int *cur_arg, int ac, char **av);
void	read_players(int cur_arg, int ac, char **av);
void	numerate_remaining_players(void);
void	validate_numeration(void);
void	set_players(void);

/*
** PROCESSES
*/


void	proc_invalid(void *data);
void	proc_live(void *data);

/*
** PROC TOOLS
*/

void	parse_command(t_process *p);
void	new_process(int pc, int playernum, t_process **start);
void	gen_processes(void);
void	free_proc(t_process *proc);
void	you_gonna_die_bitch(void);

/*
** ERRORS
*/

void	mall_error(void);
void	print_usage(void);
void	invalid_flag(char *str);
void	not_a_champion(char *str);
void	invalid_palyer_index(char *str);
void	invalid_champion(char *str);
void	file_error(char *filename);

/*
** print field
*/

void		print_field(void);
//int		curse(void);
#endif
