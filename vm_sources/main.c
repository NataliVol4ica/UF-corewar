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
		file_error(name);
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
		file_error(name);
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

_Bool	parse_n_flag(int *cur_arg, int ac, char **av)
{
	_Bool	inv_ind;
	int		index;

	inv_ind = 0;
	if (av[*cur_arg][0] != '-')
		return (0);
	if (ft_strcmp(av[*cur_arg], "-n"))
		invalid_flag(av[*cur_arg]);
	*cur_arg = *cur_arg + 1;
	if (*cur_arg >= ac)
		print_usage();
	index = ft_atoi(av[*cur_arg]) - 1;
	if (index < 0 || index > MAX_PLAYERS - 1 || g_taken_index[index])
		inv_ind = 1;
	else
	{
		g_players[g_num_of_players].index = index;
		g_taken_index[index] = 1;
	}
	*cur_arg = *cur_arg + 1;
	if (*cur_arg >= ac)
		print_usage();
	return (inv_ind);
}

void	numerate_remaining_players()
{
	int		i;
	int		j;

	i = g_num_of_players;
	while (i)
	{
		i--;
		if (g_players[g_num_of_players].index >= 0)
			continue ;
		j = -1;
		while (++j < MAX_PLAYERS)
			if (!g_taken_index[j])
			{
				g_players[g_num_of_players].index = j;
				break;
			}
	}
}

void	validate_numeration()
{
	int		i;
	int		j;

	i = MAX_PLAYERS;
	while (i > g_num_of_players)
	{
		i--;
		if (g_taken_index[i])
		{
			j = -1;
			while (++j < g_num_of_players)
				if (g_players[j].index == i)
					invalid_palyer_index(g_players[j].filename);
		}
	}
}

void	read_players(int cur_arg, int ac, char **av)
{
	_Bool	inv_ind;

	alloc_players();
	while (cur_arg < ac)
	{
		if (g_num_of_players == MAX_PLAYERS)
			print_usage();
		inv_ind = parse_n_flag(&cur_arg, ac, av);
		g_players[g_num_of_players].filename = av[cur_arg];
		parse_player(av[cur_arg], &g_players[g_num_of_players]);
		if (inv_ind)
			invalid_palyer_index(av[cur_arg]);
		g_num_of_players++;
		cur_arg++;
	}
	if (g_num_of_players == 0)
		print_usage();
}

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
