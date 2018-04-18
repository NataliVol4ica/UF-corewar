/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_ldi.c                                         :+:      :+:    :+:   */
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

void			proc_ldi(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[3];

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	toskip += CODING_BYTE;
	if (!cod_b.t[0] || (cod_b.t[1] != TDIR && cod_b.t[1] != TREG) || cod_b.t[2] != TREG)
	{
		print_move(proc, count_total_skip(cod_b, 1, 3, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 3, proc->label_size));
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip) ||
		!parse_arg(cod_b.t[2], proc, &arg[2], &toskip))
	{
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 3, proc->label_size));
		return ;
	}
	//ft_printf("P%5d | ldi ", proc->secret_num + 1);
	if (cod_b.t[0] == TREG)
	{
	//	ft_printf("r%d ", arg[0]);
		arg[0] = proc->registry[arg[0]];
	}
	else if (cod_b.t[0] == TIND)
	{
	//	ft_printf("%d ", arg[0]);
		arg[0] = get_int(proc->pc + (short)(arg[0]) % IDX_MOD, 4);
	}
	else
	//	ft_printf("%d ", arg[0]);
	if (cod_b.t[1] == TREG)
	{
	//	ft_printf("r%d ", arg[1]);
		arg[1] = proc->registry[arg[1]];
	}
	//else
	//	ft_printf("%d ", arg[1]);
	//ft_printf("r%d\n", arg[2]);
	proc->registry[arg[2]] = get_int(proc->pc + (arg[0] + arg[1]) % IDX_MOD, 4);
	//ft_printf("       | -> load from %d + %d = %d ", arg[0], arg[1], arg[0] + arg[1]);
	//ft_printf("(with pc and mod %d)\n", proc->pc + (arg[0] + arg[1]) % IDX_MOD);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
