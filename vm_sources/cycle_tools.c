/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_tools.c                                      :+:      :+:    :+:   */
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

void	you_gonna_die_bitch(void)
{
	t_process	*temp;
	t_process	*prev;
	int			i;

	temp = *g_g.proc;
	while (temp)
	{
		if (temp->live)
		{
			temp->live = 0;
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
	i = -1;
	while (++i < g_g.num_of_players)
		g_g.live[i] = 0;
	//////
}

void	run_cycle_step(int cycle)
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
			if (g_g.to_visualise ==1)
				draw_new(proc->pc);
			ft_printf("cycle %0.3d pc [%0.4d] |%0.2x|\n", cycle + 1, proc->pc, g_g.field[proc->pc]);
			ft_printf("parsing ");
			proc->func((void*)proc);
			parse_command(proc);
			if (g_g.to_visualise)
				draw_new(proc->pc);
			ft_printf("finished\n");
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
		//cycle to die //checks
		return ;
	}
	g_g.checks++;
	//chechs
}
