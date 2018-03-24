/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_load.c                                        :+:      :+:    :+:   */
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

void			proc_load(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[2];

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	toskip += CODING_BYTE;
	//ft_printf("field %#x : %b %b %b\n", get_field_val(proc->pc), cod_b.t[0], cod_b.t[1], cod_b.t[2]);
	if ((cod_b.t[0] != TDIR && cod_b.t[0] != TIND) || cod_b.t[1] != TREG)
	{
		proc->pc = set_pos(proc->pc + toskip);
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip))
	{
		proc->pc = set_pos(proc->pc +  + count_total_skip(cod_b, 1, 2));
		return ;
	}
	if (cod_b.t[0] == TIND)
		arg[0] = get_int(proc->pc + (arg[0] % IDX_MOD), 4);
	proc->registry[arg[1]] = arg[0];
	if (arg[0] == 0)
		proc->carry = 1;
	//ft_printf("reg %d is %0.8x\n", arg[1], proc->registry[arg[1]]);
	proc->pc = set_pos(proc->pc + toskip);
}