/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_invalid.c                                     :+:      :+:    :+:   */
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

void	proc_invalid(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	//print_move(proc, 1);
	proc->pc = set_pos(proc->pc + 1);
}
