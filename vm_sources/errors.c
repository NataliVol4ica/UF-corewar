/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:27:34 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:27:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "op.h"

void	mall_error(void)
{
	ft_printf("Error: Malloc fail!\n");
	exit(1);
}

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles]");
	ft_printf(" [[-n number] champion1.cor] ...\n");
	ft_printf("NOTE: The total number of players must be between 1 and %d\n",
		MAX_PLAYERS);
	exit(0);
}

void	invalid_flag(char *str)
{
	ft_printf("Invalid flag: %s\n", str);
	print_usage();
	exit(0);
}

void	not_a_champion(char *str)
{
	ft_printf("\"%s\" is not a champion!\n", str);
	system("afplay mp3/smile.mp3");
	exit(0);
}

void	invalid_palyer_index(char *str)
{
	ft_printf("Champion \"%s\" has an invalid number!\n", str);
	exit(0);
}

void	invalid_champion(char *str)
{
	ft_printf("Champion \"%s\" is invalid for some reason.\n", str);
	exit(0);
}

void	file_error(char *filename)
{
	ft_printf("\"%s\": %s\n", filename, strerror(errno));
	exit(0);
}
