/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:55 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 16:11:55 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

long			g_dump_cycle = -1;
int				g_num_of_players = 0;
t_champ			g_players[MAX_PLAYERS];
_Bool			g_taken_index[MAX_PLAYERS] = {0, 0, 0, 0};
unsigned char	*g_field;
