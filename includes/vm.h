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

# define UCHAR unsigned char
# define NUM_OF_FUNCS 4

# define COMMAND 1
# define CODING_BYTE 1
# define TREG 1
# define TDIR 2
# define TIND 3

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

int		count_total_skip(t_codes c_b, _Bool has_coding, int numofargs);
int		get_int(int pos, int len);
void	set_int(int pos, int len, int val);
_Bool	parse_arg(int code, t_process *proc, int *arg, int *toskip);
_Bool	parse_long_arg(int code, t_process *proc, int *arg, int *toskip);

void	proc_invalid(void *data);
void	proc_live(void *data);
void	proc_load(void *data);
void	proc_store(void *data);
void	proc_zjump(void *data);

/*
** PROC TOOLS
*/

void	parse_command(t_process *p);
void	new_process(int pc, int playernum, t_process **start);
void	gen_processes(void);
void	free_proc(t_process *proc);
void	you_gonna_die_bitch(void);

/*
** FIELD TOOLS
*/

UCHAR	get_field_val(int pos);
void	set_field_val(int pos, unsigned char val);
int		set_pos(int pos);
t_codes	coding_byte(int pos);

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
