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
#include "vm.h"

extern t_global	g_g;
extern t_func	g_funcs[];
extern t_curs	*g_b;

void	print_winner(void)
{
	ft_printf("Player %d ", g_g.last_live + 1);
	ft_printf("(%s) won.\n", g_g.players[g_g.last_live].name);
	exit(0);
}

int		main(int ac, char **av)
{
	parse_input(ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
	if (g_g.dump_cycle == 0)
		print_field();
	if (g_g.to_visualise)
		curse();
	else
		print_participants();
	gen_processes();
	while (1)
	{
		if (g_g.kill == 1)
			g_g.kill = 0;
		if (!*g_g.proc)
			break;
		if (g_g.to_visualise)
			++g_b->cycle/* += 1*/;
		//ft_printf("====|| cycle %0.4d \n", total_cycle);
		run_cycle_step();
		if (g_g.cycle == g_g.cycle_to_die)
		{
			//ft_printf("cycle %d ctdie %d\n", cycle, g_g.cycle_to_die);
			g_g.cycle = 0;
			you_gonna_die_bitch();
			ctd_check();
			g_g.period_lives = 0;
		}
		g_g.cycle++;
		g_g.total_cycle++;
		if (g_g.total_cycle == g_g.dump_cycle)
			print_field();
		if (g_g.to_visualise)
			readkey();
		//if (total_cycle == 1500)
		//	exit(0);
	}
	if (g_g.to_visualise)
	{
		pashalka();
		exit_curse_main();
	}
	// close(g_b->fd);
	// close(g_b->fd3);
	// close(g_b->fd4);
	print_winner();
 	return (0);
}
