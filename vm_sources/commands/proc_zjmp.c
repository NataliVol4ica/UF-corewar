/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_zjmp.c                                        :+:      :+:    :+:   */
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

void			proc_zjump(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	//ft_printf("field %#x\n", get_field_val(proc->pc));
	if (proc->carry)
		proc->pc = set_pos(proc->pc + get_int(proc->pc + 1, 2));
	else
		proc->pc = set_pos(proc->pc + 3);
	proc->carry = 0;
}
