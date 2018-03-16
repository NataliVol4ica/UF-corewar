/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:37:08 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:37:12 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# define MALL(x) if (!(x)) mall_error()

# include "structures.h"

/*
** PLAYER READING
*/

void	parse_player(char *name, t_champ *player);
_Bool	parse_n_flag(int *cur_arg, int ac, char **av);
void	read_players(int cur_arg, int ac, char **av);
void	numerate_remaining_players();
void	validate_numeration();

/*
** ERRORS
*/

void	mall_error(void);
void	print_usage(void);
void	invalid_flag(char *str);
void	not_a_champion(char *str);
void	invalid_palyer_index(char *str);
void	invalid_champion(char *str);
void	file_error(char *filename);

#endif
