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

void	print_move(t_process *proc, int toskip)
{
	int i = -1;
	int oldpc;

	if (!g_g.log_flag || g_g.to_visualise)
		return ;
	oldpc = proc->pc;
	ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", toskip, proc->pc, proc->pc + toskip);
	while (++i < toskip)
		ft_printf("%02x ", get_field_val(proc->pc + i));
	ft_printf("\n");
}

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
	if ((cod_b.t[0] != TDIR && cod_b.t[0] != TIND) || cod_b.t[1] != TREG)
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip))
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	//ft_printf("P%5d | ld ", proc->secret_num + 1);
	if (cod_b.t[0] == TIND)
	{
		arg[0] = get_int(proc->pc + ((short)(arg[0]) % IDX_MOD), 4);
	}
	//ft_printf("%d", arg[0]);
	proc->registry[arg[1]] = arg[0];
	if (proc->registry[arg[1]] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	//ft_printf(" r%d\n", arg[1]);
	//ft_printf("reg %d is %0.8x\n", arg[1], proc->registry[arg[1]]);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
