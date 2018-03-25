/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:55 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 16:11:55 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_global	g_g;
t_curs		*g_b;
t_func		g_funcs[] =
{
	{0x01, &proc_live, 10},
	{0x02, &proc_load, 5},
	{0x03, &proc_store, 5},
	{0x04, &proc_add, 10},
	{0x05, &proc_sub, 10},
	{0x06, &proc_and, 6},
	{0x07, &proc_or, 6},
	{0x08, &proc_xor, 6},
	{0x09, &proc_zjump, 20},
	{0x0a, &proc_ldi, 25},
	{0x0b, &proc_sti, 25},
	{0x0c, &proc_fork, 800},
	{0x0d, &proc_load_long, 10},
	{0x0e, &proc_ldi_long, 50},
	{0x0f, &proc_fork_long, 1000},
	{0x10, &proc_aff, 2}
};
