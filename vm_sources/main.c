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
extern t_curs	*g_b;

void	parse_command(t_process *p)
{
	int i;

	i = -1;
	while (++i < NUM_OF_FUNCS)
		if (g_g.field[p->pc] == g_funcs[i].hex)
		{
			p->func = g_funcs[i].func;
			p->sleep = g_funcs[i].sleep;
			break ;
		}
	if (i == NUM_OF_FUNCS)
	{
		p->func = &proc_invalid;
		p->sleep = 1;
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
		//ft_printf("prs#%d ind[%x] pos %0.4d(%0.2x) sleep %d\n", i, proc->registry[0], proc->pc, g_g.field[proc->pc], proc->sleep);
		if (proc->sleep == 0)
		{
			//erase_old(proc->pc);
			draw_new(proc->pc);
			proc->func((void*)proc);
			//ft_printf("parsing ");
			parse_command(proc);
			draw_new(proc->pc);
			//ft_printf("finished\n");
		}
		proc = proc->next;
	}
}

void	ctd_check(void)
{
	if (g_g.period_lives >= NBR_LIVE || g_g.checks == MAX_CHECKS)
	{
		g_g.cycle_to_die -= CYCLE_DELTA;
		if (g_g.cycle_to_die < 1)
			g_g.cycle_to_die = 1;
		g_g.checks = 0;
		g_g.period_lives = 0;
		return ;
	}
	g_g.checks++;
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
	if (!ft_strcmp("-v", av[cur_arg]))
	{
		cur_arg++;
		g_g.to_visualise = 1;
	}	read_players(cur_arg, ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
	if (g_g.dump_cycle == 0)
		print_field();
	//algo
	gen_processes();
	cycle = 0;
	total_cycle = 0;
	curse();
	while (1)
	{
		g_b->cycle += 1;
		if (!*g_g.proc)
			break;
		//ft_printf("====|| cycle %0.4d \n", total_cycle);
		run_cycle_step();
		if (cycle == g_g.cycle_to_die)
		{
			//ft_printf("cycle %d ctdie %d\n", cycle, g_g.cycle_to_die);
			cycle = 0;
			you_gonna_die_bitch();
			ctd_check();
			g_g.period_lives = 0;
		}
		cycle++;
		total_cycle++;
		if (total_cycle == g_g.dump_cycle)
			print_field();
		readkey();
	}
	pashalka();
	exit_curse();
	print_winner();
 	return (0);
}
