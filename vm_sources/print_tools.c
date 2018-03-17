/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:51:45 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 17:51:46 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <stdlib.h>

extern int				g_num_of_players;
extern t_champ			g_players[MAX_PLAYERS];
extern unsigned char	*g_field;

void		set_players(void)
{
	int	i;
	int j;

	i = -1;
	while (++i < g_num_of_players)
		g_players[i].startpos = /*g_players[i].index*/i * MEM_SIZE /
			g_num_of_players;
	MALL(g_field =
		(unsigned char*)ft_memalloc(sizeof(unsigned char) * MEM_SIZE));
	i = -1;
	while (++i < g_num_of_players)
	{
		j = -1;
		while (++j < g_players[i].field_size)
			g_field[j + g_players[i].startpos] = g_players[i].field[j];
	}
}

void		print_field(void)
{
	int	i;

	ft_printf(" || PARTICIPANTS: ||\n");
	i = -1;
	while (++i < g_num_of_players)
	{
		ft_printf("=============// Player[%d]\n", i + 1);
		ft_printf("\tName:    \"%.*s\"\n", PROG_NAME_LENGTH,
			g_players[i].name);
		ft_printf("\tWeight:   %d\n", g_players[i].field_size);
		ft_printf("\tComment: \"%.*s\"\n", COMMENT_LENGTH,
			g_players[i].comment);
	}
	ft_printf("\n ||    FIELD:     || \n");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%0.4x |", i);
		ft_printf(" %02x", g_field[i]);
		if (i % 64 == 63)
			ft_printf("\n");
	}
	exit(0);
}
