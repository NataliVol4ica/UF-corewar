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

extern long	g_dump_cycle;

int		main(int ac, char **av)
{
	int		cur_arg;

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
	//set players data
	return (0);
}
