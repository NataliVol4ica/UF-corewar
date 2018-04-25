/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_store.c                                       :+:      :+:    :+:   */
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

void			proc_sti(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[3];

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	//if (proc->secret_num == 13)
	//	ft_printf("val[%d] = %02x\n", proc->pc + toskip, get_field_val(proc->pc + toskip));
	toskip += CODING_BYTE;
	if (cod_b.t[0] != TREG || !cod_b.t[1] || (cod_b.t[2] != TDIR && cod_b.t[2] != TREG))
	{
		//ft_printf("total skip1 %d\n", count_total_skip(cod_b, 1, 3, proc->label_size));
		print_move(proc, count_total_skip(cod_b, 1, 3, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 3, proc->label_size));
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip) ||
		!parse_arg(cod_b.t[2], proc, &arg[2], &toskip))
	{
		//ft_printf("total skip2 %d\n", count_total_skip(cod_b, 1, 3, proc->label_size));
		print_move(proc, count_total_skip(cod_b, 1, 3, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 3, proc->label_size));
		//if (proc->secret_num == 13)
		//	ft_printf("sti failed2\n");
		//print_move(proc, toskip);
		return ;
	}
	if (TOCOMMENT)
		ft_printf("P%5d | sti ", proc->secret_num + 1);
	if (TOCOMMENT)
		ft_printf("r%d ", arg[0]);
	arg[0] = proc->registry[arg[0]];

	if (cod_b.t[1] == TREG)
		arg[1] = proc->registry[arg[1]];
	else if (cod_b.t[1] == TIND)
		arg[1] = get_int(proc->pc + (short)(arg[1]) % IDX_MOD, 4);
	if (TOCOMMENT)
		ft_printf("%d ", arg[1]);
	if (cod_b.t[2] == TREG)
		arg[2] = proc->registry[arg[2]];
	if (TOCOMMENT)
		ft_printf("%d\n", arg[2]);
	set_int(proc->pc + (arg[1] + arg[2]) % IDX_MOD, 4, arg[0], proc->index);
	if (TOCOMMENT)
		ft_printf("       | -> store to %d + %d = %d ", arg[1], arg[2], arg[1] + arg[2]);
	if (TOCOMMENT)
		ft_printf("(with pc and mod %d)\n", proc->pc + (arg[1] + arg[2]) % IDX_MOD);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
