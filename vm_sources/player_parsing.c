/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:27:01 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 15:27:01 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>
#include <unistd.h>

extern int		g_num_of_players;
extern t_champ	g_players[MAX_PLAYERS];
extern _Bool	g_taken_index[MAX_PLAYERS];

_Bool		parse_n_flag(int *cur_arg, int ac, char **av)
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
	if (index < 0 || index > MAX_PLAYERS - 1 ||
		g_taken_index[index])
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

static void	parse_magic_number(char *name, int fd)
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

void		parse_player(char *name, t_champ *player)
{
	int		fd;
	int		ret;
	char	temp[1];
	int		i;

	if ((fd = open(name, O_RDONLY)) < 0)
		file_error(name);
	parse_magic_number(name, fd);
	if ((ret = read(fd, player->name, PROG_NAME_LENGTH)) <
		PROG_NAME_LENGTH)
		invalid_champion(name);
	if ((ret = read(fd, player->comment, COMMENT_LENGTH)) <
		COMMENT_LENGTH)
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
