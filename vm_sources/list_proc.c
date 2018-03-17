/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 21:05:58 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/16 21:06:00 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>
#include <string.h>
/*
*** use only when we init proc in start
*/

t_proc *lst_proc_new_start(t_champ cur, int index)
{
	t_proc *res;

	if (!(res = ft_memalloc(sizeof(t_proc))))
		mall_error();
	res->live = 1;
	res->id = (index + 1) * (-1);
	res->reg[0] = (index + 1) * -1;
	res->pc = cur.startpos;
	ft_printf("pc %d\n", res->pc);
	res->next = NULL;
	res->name = strdup(cur.name);
	ft_printf("cur.name %s\n", res->name);
	return (res);
}

/*
*** push back node with proc
*/

void	lst_proc_push_back(t_proc **alst, t_proc *new)
{
	t_proc *cur;

	if (!alst)
		return ;
	else if (!(*alst))
		(*alst) = new;
	else
	{
		cur = (*alst);
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

/*
*** push front nide with proces
*/

void	lst_proc_add(t_proc **alst, t_proc *new)
{
	if (!alst)
		exit(1);
	new->next = (*alst);
	(*alst) = new;
}

/*
*** kill all dead proces
*/

void	lst_del_dead_proc(t_proc **alst)
{
	t_proc *cur;
	t_proc *prev;

	cur = (*alst);
	prev = cur;
	while (cur)
	{
		if (cur->live == 0 && cur == *alst)
		{
			prev = cur->next;
			free(cur);
			cur = prev;
			*alst = cur;
			system("afplay mp3/reset.mp3");
			system("afplay mp3/fire.mp3");
			system("afplay mp3/cry.mp3");
			system("afplay mp3/ura.mp3");
		}
		else if (cur->live == 0)
		{
			prev->next = cur->next;
			free(cur);
			cur = prev->next;
			system("afplay mp3/reset.mp3");
			system("afplay mp3/fire.mp3");
			system("afplay mp3/cry.mp3");
			system("afplay mp3/ura.mp3");
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
