/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:38 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:35:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
# include <ncurses.h>
extern long				g_dump_cycle;
extern int				g_num_of_players;
extern t_champ			g_players[MAX_PLAYERS];
extern unsigned char	*g_field;
extern t_process		**g_proc;
extern t_func			g_funcs[];

void	parse_command(t_process *p)
{
	int i;

	i = -1;
	while (++i < NUM_OF_FUNCS)
		if (g_field[p->pc] == g_funcs[i].hex)
		{
			p->func = g_funcs[i].func;
			p->sleep = g_funcs[i].sleep;
			break;
		}
	if (i == NUM_OF_FUNCS)
	{
		p->func = &proc_invalid;
		p->sleep = 1;
	}
}

void	new_process(int pc, int playernum, t_process **start)
{
	int			i;
	t_process	*new_proc;

	MALL(new_proc = (t_process*)ft_memalloc(sizeof(t_process)));
	new_proc->index = playernum;
	MALL(new_proc->registry = (unsigned int*)ft_memalloc(sizeof(unsigned int) * REG_NUMBER));
	new_proc->registry[0] = -playernum;
	new_proc->pc = pc;
	new_proc->carry = 1;
	new_proc->live = 0;
	new_proc->next = *start;
	*start = new_proc;
	parse_command(new_proc);
	//call draw at pc pos
}

void	gen_processes(void)
{
	int	i;
	int j;

	MALL(g_proc = (t_process**)malloc(sizeof(t_process*)));
	*g_proc = NULL;
	i = -1;
	while (++i < g_num_of_players)
	{
		j = -1;
		while (++j < g_num_of_players)
			if (g_players[j].index == i)
			{
				new_process(g_players[j].startpos, j, g_proc);
				break;
			}
	}
}

void	run_cycle_step(void)
{
	int			i;
	t_process	*proc;
	
	i = 0;
	proc = *g_proc;
	while (proc)
	{
		proc->sleep--;
		ft_printf("prs#%d ind[%d] pos %0.4d(%0.2x) sleep %d\n", i, proc->index, proc->pc, g_field[proc->pc], proc->sleep);
		if (proc->sleep == 0)
		{
			proc->func((void*)proc);
			parse_command(proc);
		}
		proc = proc->next;
	}
}

int		main(int ac, char **av)
{
	int		cur_arg;
	int		cycle;
	int		total_cycle;

	cur_arg = 1;
	if (cur_arg >= ac)
		print_usage();
	if (!ft_strcmp("-dump", av[cur_arg]))
	{
		if (cur_arg + 1 >= ac)
			print_usage();
		cur_arg++;
		if (!(is_number(av[cur_arg])) ||
			(g_dump_cycle = ft_atoi(av[cur_arg])) < 0)
			print_usage();
		cur_arg++;
	}
	//parse additional flags here
	read_players(cur_arg, ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
	//algo
	gen_processes();
	cycle = 0;
	total_cycle = 0;
	curse();
	// while (1)
	// {
	// 	ft_printf("cycle %0.4d | ", total_cycle);
	// 	run_cycle_step();
	// 	if (cycle == CYCLE_TO_DIE)
	// 	{
	// 		cycle = 0;
	// 		//check and zero alive processes
	// 		break;
	// 	}
	// 	cycle++;
	// 	total_cycle++;
	// }
 	return (0);
}
