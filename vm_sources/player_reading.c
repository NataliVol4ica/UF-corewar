/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_reading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:26:53 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 15:26:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern int		g_num_of_players;
extern t_champ	g_players[MAX_PLAYERS];
extern _Bool	g_taken_index[MAX_PLAYERS];

static void	alloc_players(void)
{
	int	i;
	int	j;

	j = -1;
	while (++j < 4)
	{
		g_players[j].index = -1;
		i = -1;
		while (++i < PROG_NAME_LENGTH)
			g_players[j].name[i] = 0;
		i = -1;
		while (++i < COMMENT_LENGTH)
			g_players[j].comment[i] = 0;
		i = -1;
		while (++i < CHAMP_MAX_SIZE)
			g_players[j].field[i] = 0;
	}
}

void		read_players(int cur_arg, int ac, char **av)
{
	_Bool	inv_ind;

	alloc_players();
	while (cur_arg < ac)
	{
		if (g_num_of_players == MAX_PLAYERS)
			print_usage();
		inv_ind = parse_n_flag(&cur_arg, ac, av);
		g_players[g_num_of_players].filename = av[cur_arg];
		parse_player(av[cur_arg], &g_players[g_num_of_players]);
		if (inv_ind)
			invalid_palyer_index(av[cur_arg]);
		g_num_of_players++;
		cur_arg++;
	}
	if (g_num_of_players == 0)
		print_usage();
}

void		numerate_remaining_players(void)
{
	int		i;
	int		j;

	i = g_num_of_players;
	while (i)
	{
		i--;
		if (g_players[i].index >= 0)
			continue ;
		j = -1;
		while (++j < MAX_PLAYERS)
			if (!g_taken_index[j])
			{
				g_players[i].index = j;
				g_taken_index[j] = 1;
				break ;
			}
	}
}

void		validate_numeration(void)
{
	int		i;
	int		j;

	i = MAX_PLAYERS;
	while (i > g_num_of_players)
	{
		i--;
		if (g_taken_index[i])
		{
			j = -1;
			while (++j < g_num_of_players)
				if (g_players[j].index == i)
					invalid_palyer_index(g_players[j].filename);
		}
	}
}
