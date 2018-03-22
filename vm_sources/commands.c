/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
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

int		get_two_bits(int pos, int from)
{
	int t;
	int	i;

	t = g_g.field[pos];
	t = t << from;
	t = (unsigned char)t;
	t = t >> (6 - from);
	return (t);
}

void	proc_invalid(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	//alert position movement
}

void	proc_live(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	proc->live++;
	proc->pc = (proc->pc + 5) % MEM_SIZE;
	g_g.period_lives++;
	//alert pos movement
	//alert player life incr
}

void	proc_load(void *data)
{
	t_process	*proc;
	int			ret;

	proc = (t_process*)data;
	ret = get_two_bits(proc->pc, 0);
	if (ret == T_DIR)
	{
		;
	}
	else if (ret == T_IND)
	{
		;
	}
	else
	{
		proc->pc = (proc->pc + 2) % MEM_SIZE;
		return ;
	}
	ret = get_two_bits(proc->pc, 2);
	if (ret == T_REG)
	{
		;
	}
	else
	{
		proc->pc = (proc->pc + 2) % MEM_SIZE;
		return ;
	}
	proc->pc = (proc->pc + 6) % MEM_SIZE;
}
