/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern t_global	g_g;

unsigned char	get_field_val(int pos)
{
	//ft_printf("WTF?! [%d] %0.2x\n", pos % MEM_SIZE, g_g.field[pos % MEM_SIZE]);
	return (g_g.field[(MEM_SIZE + pos) % MEM_SIZE]);
}

void			set_field_val(int pos, unsigned char val, int playernum)
{
	if (TOCOMMENT)
		ft_printf("player #%d rewriting %0.2x to %0.2x at %d\n", playernum, g_g.field[(MEM_SIZE + pos) % MEM_SIZE], val, (MEM_SIZE + pos) % MEM_SIZE);
	g_g.field[(MEM_SIZE + pos) % MEM_SIZE] = val;
	if (g_g.to_visualise == 1)
		load_player((MEM_SIZE + pos) % MEM_SIZE, playernum);
}

int				set_pos(int pos)
{
	return ((MEM_SIZE + pos) % MEM_SIZE);
}

static int		get_two_bits(int pos, int from)
{
	int t;

	t = get_field_val(pos);
	t = t << from;
	t = (unsigned char)t;
	t = t >> 6;
	return (t);
}

t_codes			coding_byte(int pos)
{
	t_codes	ans;

	if (TOCOMMENT)
		ft_printf("%0.2x %b\n", get_field_val(pos), get_field_val(pos));
	ans.t[0] = get_two_bits(pos, 0);
	ans.t[1] = get_two_bits(pos, 2);
	ans.t[2] = get_two_bits(pos, 4);
	return (ans);
}
