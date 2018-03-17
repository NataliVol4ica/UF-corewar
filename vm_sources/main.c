/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:38 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:35:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern long		g_dump_cycle;
extern int		g_num_of_players;
extern t_champ	g_players[MAX_PLAYERS];
//extern t_proc	*alst;


void	make_proc_at_start(t_proc **alst)
{
	int i = 0;
	int a = 0;
	int count = 0;
	while (a < MAX_PLAYERS && g_players[a].index != -1)
	{
		while (i < MAX_PLAYERS && g_players[i].index != -1)
		{
			if (g_players[i].index == count)
			{
				lst_proc_push_back(alst, lst_proc_new_start(g_players[i], i));
				count++;
			}
			i++;
		}
		i = 0;
		a++;
	}
}

int		main(int ac, char **av)
{
	int		cur_arg;
	t_proc	*alst = NULL; //poiner to start proc node

	cur_arg = 1;
	if (cur_arg >= ac)
		print_usage();
	if (!ft_strcmp("-dump", av[cur_arg]))
	{
		if (cur_arg + 1 >= ac)
			print_usage();
		cur_arg++;
		if (!(is_number(av[cur_arg])) ||
			(g_dump_cycle = ft_atoi(av[cur_arg])) < 0)
			print_usage();
		cur_arg++;
	}
	//parse additional flags here
	read_players(cur_arg, ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
//	print_field();
	
	make_proc_at_start(&alst);

//////////////////TESTING PART //////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	alst->live = 0;
	lst_del_dead_proc(&alst); //dell(kill) proc after start;

	t_proc *tmp;
	tmp = alst;
	while (tmp)
	{
		ft_printf("id %d name %s PC %d\n", tmp->id, tmp->name, tmp->pc);
		tmp = tmp->next;
	}

/////////////////////////////////////////////////////////////////////////////////
	int index = -1;
	ft_printf("MAX_PLAYERS %d\n\n", MAX_PLAYERS);
	while (++index < MAX_PLAYERS && g_players[index].index != -1)
		ft_printf("index = %d name %s file name %s\n", g_players[index].index, g_players[index].name, g_players[index].filename);
 	return (0);
}
