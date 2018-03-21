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
#include <ncurses.h>

extern t_global	g_g;
extern t_func	g_funcs[];

void	parse_command(t_process *p)
{
	int i;

	i = -1;
	while (++i < NUM_OF_FUNCS)
		if (g_g.field[p->pc] == g_funcs[i].hex)
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
	MALL(new_proc->registry = (unsigned int*)ft_memalloc(sizeof(unsigned int) * REG_NUMBER));
	new_proc->registry[0] = -playernum;
	new_proc->pc = pc;
	new_proc->carry = 1;
	new_proc->live = 0;
	new_proc->next = *start;
	*start = new_proc;
	parse_command(new_proc);
	//draw_new(new_proc->pc)
}

void	gen_processes(void)
{
	int	i;
	int j;

	i = -1;
	while (++i < g_g.num_of_players)
	{
		j = -1;
		while (++j < g_g.num_of_players)
			if (g_g.players[j].index == i)
			{
				new_process(g_g.players[j].startpos, j, g_g.proc);
				break;
			}
	}
}

void	run_cycle_step(void)
{
	int			i;
	t_process	*proc;
	
	i = 0;
	proc = *g_g.proc;
	while (proc)
	{
		proc->sleep--;
		ft_printf("prs#%d ind[%d] pos %0.4d(%0.2x) sleep %d\n", i, proc->registry[0], proc->pc, g_g.field[proc->pc], proc->sleep);
		if (proc->sleep == 0)
		{
			//erase_old(proc->pc);
			proc->func((void*)proc);
			parse_command(proc);
			//draw_new(proc->pc);
		}
		proc = proc->next;
	}
}

void	free_proc(t_process *proc)
{
	//call death function
	free(proc->registry);
	free(proc);
}

void	you_gonna_die_bitch(void)
{
	t_process	*temp;
	t_process	*prev;

	temp = *g_g.proc;
	while (temp)
	{
		if (temp->live)
		{
			prev = temp;
			temp = temp->next;
			continue;
		}
		if (temp == *g_g.proc)
		{
			temp = (*g_g.proc)->next;
			free_proc(*g_g.proc);
			*g_g.proc = temp;
			continue;
		}
		temp = temp->next;
		free_proc(prev->next);
		prev->next = temp;
	}
}

static void	alloc_players(void)
{
	int	i;
	int	j;

	j = -1;
	while (++j < MAX_PLAYERS)
	{
		g_g.players[j].index = -1;
		i = -1;
		while (++i < PROG_NAME_LENGTH)
			g_g.players[j].name[i] = 0;
		i = -1;
		while (++i < COMMENT_LENGTH)
			g_g.players[j].comment[i] = 0;
		i = -1;
		while (++i < CHAMP_MAX_SIZE)
			g_g.players[j].field[i] = 0;
		g_g.taken_index[j] = 0;
	}
}

void	init_globals(void)
{
	g_g.dump_cycle = -1;
	g_g.num_of_players = 0;
	alloc_players();
	MALL(g_g.field =
		(unsigned char*)ft_memalloc(sizeof(unsigned char) * MEM_SIZE));
	MALL(g_g.proc = (t_process**)malloc(sizeof(t_process*)));
	*g_g.proc = NULL;
	g_g.period_lives = 0;
}

int		main(int ac, char **av)
{
	int		cur_arg;
	int		cycle;
	int		total_cycle;

	cur_arg = 1;
	if (cur_arg >= ac)
		print_usage();
	init_globals();
	if (!ft_strcmp("-dump", av[cur_arg]))
	{
		if (cur_arg + 1 >= ac)
			print_usage();
		cur_arg++;
		if (!(is_number(av[cur_arg])) ||
			(g_g.dump_cycle = ft_atoi(av[cur_arg])) < 0)
			print_usage();
		cur_arg++;
	}
	//parse additional flags here
	read_players(cur_arg, ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
	if (g_g.dump_cycle == 0)
		print_field();
	//algo
	gen_processes();
	cycle = 0;
	total_cycle = 0;
	//curse();
	while (1)
	{
		ft_printf("cycle %0.4d | ", total_cycle);
		run_cycle_step();
		if (cycle == CYCLE_TO_DIE)
		{
			cycle = 0;
			you_gonna_die_bitch();
			g_g.period_lives = 0;
			break;
		}
		cycle++;
		total_cycle++;
		if (total_cycle == g_g.dump_cycle)
			print_field();
		//readkey();
	}
 	return (0);
}
