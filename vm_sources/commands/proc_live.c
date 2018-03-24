/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

void	proc_live(void *data)
{
	t_process		*proc;
	unsigned char	l;

	proc = (t_process*)data;
	proc->live++;
	proc->pc = set_pos(proc->pc + 5);
	g_g.period_lives++;
	l = get_int(proc->pc + 1, 4);
	if (l >= g_g.num_of_players)
		return ;
//	ft_printf("A process shows that player %d ", l);
//	ft_printf("(%s) is alive.\n", g_g.players[l].name);
	g_g.last_live = l;
	g_g.live[l]++;
	//////
}
