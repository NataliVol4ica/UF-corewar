/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:08:15 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/21 16:08:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
#include <ncurses.h>

extern t_global	g_g;

void	new_process(int pc, int playernum, t_process **start)
{
	int			i;
	t_process	*new_proc;

	MALL(new_proc = (t_process*)ft_memalloc(sizeof(t_process)));
	MALL(new_proc->registry =
		(unsigned int*)ft_memalloc(sizeof(unsigned int) * REG_NUMBER));
	new_proc->index = playernum - 1;
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
				new_process(g_g.players[j].startpos, j + 1, g_g.proc);
				break ;
			}
	}
}

void	free_proc(t_process *proc)
{
	//call death function
	free(proc->registry);
	free(proc);
}

void	print_winner(void)
{
	ft_printf("Player %d ", g_g.last_live + 1);
	ft_printf("(%s) won.\n", g_g.players[g_g.last_live].name);
	exit(0);
}

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
			g_g.live_processes--;
			if (g_g.live_processes == 0)
				print_winner();
			continue;
		}
		temp = temp->next;
		free_proc(prev->next);
		prev->next = temp;
	}
	i = -1;
	while (++i < g_g.num_of_players)
		g_g.live[i] = 0;
}
