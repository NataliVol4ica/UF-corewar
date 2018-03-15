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
#include <fcntl.h>
#include <unistd.h>

void	alloc_players()
{
	int	i;
	int	j;

	j = -1;
	while (++j < 4)
	{
		g_players[j].index = -1;
		i = -1;
		while (++i < PROG_NAME_LENGTH)
			g_players[j].name[i] = 0;
		i = -1;
		while (++i < COMMENT_LENGTH)
			g_players[j].comment[i] = 0;
		i = -1;
		while (++i < CHAMP_MAX_SIZE)
			g_players[j].field[i] = 0;

	}
}

void	parse_magic_number(char *name, int fd)
{
	int		ret;
	long	magic_number;
	char	buf[4];

	if ((fd = open(name, O_RDONLY)) < 0)
		file_error();
	if ((ret = read(fd, buf, 4)) < 4)
		not_a_champion(name);
	magic_number = (unsigned char)buf[3] +
					((unsigned char)buf[2] << 8) +
					((unsigned char)buf[1] << 16) +
					((unsigned char)buf[0] << 24);
	if (magic_number != COREWAR_EXEC_MAGIC)
		not_a_champion(name);
}

void	parse_player(char *name, t_champ *player)
{
	int		fd;
	int		ret;
	char	temp[1];
	int		i;

	if ((fd = open(name, O_RDONLY)) < 0)
		file_error();
	parse_magic_number(name, fd);
	if ((ret = read(fd, player->name, PROG_NAME_LENGTH)) < PROG_NAME_LENGTH)
		invalid_champion(name);
	if ((ret = read(fd, player->comment, COMMENT_LENGTH)) < COMMENT_LENGTH)
		invalid_champion(name);
	if ((ret = read(fd, player->field, CHAMP_MAX_SIZE)) < 0)
		invalid_champion(name);
	i = -1;
	while (++i < ret)
		player->field[i] = (unsigned char)player->field[i];
	player->field_size = ret;
	if ((ret = read(fd, temp, 1)) > 0)
		invalid_champion(name);
	close(fd);
}

int		main(int ac, char **av)
{
	int		cur_arg;
	int		index;
	_Bool	inv_ind;
	int		i;

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
	//players loop
	alloc_players();
	while (cur_arg < ac)
	{
		if (g_num_of_players == 4)
			print_usage();
		//[-n num] parse
		inv_ind = 0;
		if (av[cur_arg][0] == '-')
		{
			if (ft_strcmp(av[cur_arg], "-n"))
				invalid_flag(av[cur_arg]);
			cur_arg++;
			if (cur_arg >= ac)
				print_usage();
			index = ft_atoi(av[cur_arg]);
			if (index < 0 || index > 3 ||
				g_players[index].index != -1)
				inv_ind = 1;
			g_players[index].index = g_num_of_players;
			cur_arg++;
		}
		//player parse
		if (cur_arg >= ac)
			print_usage();
		g_players[index].filename = av[cur_arg];
		parse_player(av[cur_arg], &g_players[index]);
		if (inv_ind)
			invalid_palyer_index(av[cur_arg]);
		g_num_of_players++;
		cur_arg++;
	}
	if (g_num_of_players == 0)
		print_usage();
	//check if norm numerated
	i = 4;
	while (i > g_num_of_players)
	{
		i--;
		if (g_players[i].index >= 0)
			invalid_palyer_index(g_players[i].filename);
	}
	//set
	return (0);
}
