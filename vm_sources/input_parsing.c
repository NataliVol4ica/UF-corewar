/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:38 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:35:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

static void	parse_input2(int ac, char **av, int cur_arg)
{
	if (!ft_strcmp("-l", av[cur_arg]))
	{
		cur_arg++;
		if (!ft_strcmp("1", av[cur_arg]))
		{
			g_g.log_flag1 = 1;
			cur_arg++;
		}
		else if (!ft_strcmp("2", av[cur_arg]))
		{
			g_g.log_flag2 = 1;
			cur_arg++;
		}
		else if (!ft_strcmp("12", av[cur_arg]) ||
				!ft_strcmp("21", av[cur_arg]))
		{
			g_g.log_flag1 = 1;
			g_g.log_flag2 = 1;
			cur_arg++;
		}
		else
			print_usage();
	}
	read_players(cur_arg, ac, av);
}

void		parse_input(int ac, char **av)
{
	int		cur_arg;

	cur_arg = 1;
	if (cur_arg >= ac)
		print_usage();
	init_globals();
	if (!ft_strcmp("-dump", av[cur_arg]))
	{
		if (cur_arg + 1 >= ac)
			print_usage();
		cur_arg++;
		if (!(is_number(av[cur_arg])) ||
			(g_g.dump_cycle = ft_atoi(av[cur_arg])) < 0)
			print_usage();
		cur_arg++;
	}
	if (!ft_strcmp("-v", av[cur_arg]))
	{
		cur_arg++;
		g_g.to_visualise = 1;
	}
	parse_input2(ac, av, cur_arg);
}
