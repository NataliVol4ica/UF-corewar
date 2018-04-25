/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_aff.c                                         :+:      :+:    :+:   */
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

void			proc_aff(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			arg[1];
	int			toskip;

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	toskip += CODING_BYTE;
	if (cod_b.t[0] != TREG)
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip))
	{
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	if (!g_g.to_visualise && !g_g.log_flag)
		ft_printf("%c\n", proc->registry[arg[0]]);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + 3);
	//proc->carry = 0;
}
