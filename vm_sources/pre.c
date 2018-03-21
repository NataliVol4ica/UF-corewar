/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:13:51 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/21 16:13:52 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
#include <ncurses.h>

extern t_global	g_g;

static void	alloc_players(void)
{
	int	i;
	int	j;

	j = -1;
	while (++j < MAX_PLAYERS)
	{
		g_g.players[j].index = -1;
		MALL(g_g.players[j].name =
			(char*)ft_memalloc(sizeof(char) * PROG_NAME_LENGTH));
		MALL(g_g.players[j].comment =
			(char*)ft_memalloc(sizeof(char) * COMMENT_LENGTH));
		MALL(g_g.players[j].field =
			(unsigned char*)ft_memalloc(sizeof(unsigned char) *
				CHAMP_MAX_SIZE));
	}
}

void		init_globals(void)
{
	g_g.dump_cycle = -1;
	g_g.num_of_players = 0;
	alloc_players();
	MALL(g_g.taken_index = (_Bool*)ft_memalloc(sizeof(_Bool) * MAX_PLAYERS));
	MALL(g_g.field =
		(unsigned char*)ft_memalloc(sizeof(unsigned char) * MEM_SIZE));
	MALL(g_g.proc = (t_process**)malloc(sizeof(t_process*)));
	*g_g.proc = NULL;
	g_g.period_lives = 0;
	g_g.cycle_to_die = CYCLE_TO_DIE;
	g_g.checks = 0;
}
