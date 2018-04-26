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
#include "vm.h"

void	mall_error(void)
{
	ft_printf("Error: Malloc fail!\n");
	exit(1);
}

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles] [-v] [-l lIdx]");
	ft_printf(" [[-n number] champion1.cor] ...\n");
	ft_printf("   -dump:\n");
	ft_printf("\tafter nbr_cycles of executions, dump the memory on ");
	ft_printf("the standard output and quit the game\n");
	ft_printf("    -v:\n");
	ft_printf("\tvisual mod\n");
	ft_printf("    -l:\n");
	ft_printf("\tturn on the logs. Incompatible with -v\n");
	ft_printf("\t   1: commands log\n");
	ft_printf("\t   2: PC movement log\n");
	ft_printf("    -n:\n");
	ft_printf("\tcustom number of player\n");
	ft_printf("NOTE: The total number of players must be between 1 and %d\n",
		MAX_PLAYERS);
	exit(0);
}

void	file_error(char *filename)
{
	ft_printf("\"%s\": %s\n", filename, strerror(errno));
	exit(0);
}
