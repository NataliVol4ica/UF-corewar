/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encurse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 13:39:23 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/18 13:39:25 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCURSE_H
# define ENCURSE_H

//# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
//# include <ncurses.h>
//# include "vm.h"

# define WIN_WIDTH 260
# define WIN_HEIGHT 70

# define X_MATR_SRT 2
# define Y_MATR_SRT 2
# define X_MATR_END 196
# define Y_MATR_END 68

# define X_BAR_SRT 200
# define Y_BAR_SRT 2
# define Y_BAR_SECL 4
# define Y_BAR_CYCL 8
# define Y_BAR_PROC 10

# define Y_BAR_PL1 12
# define Y_BAR_PL1LL 13
# define Y_BAR_PL1LIC 14
# define X_BAR_SCL 202

# define Y_BAR_PL2 16
# define Y_BAR_PL2LL 17
# define Y_BAR_PL2LIC 18

# define Y_BAR_PL3 20
# define Y_BAR_PL3LL 21
# define Y_BAR_PL3LIC 22

# define Y_BAR_PL4 24
# define Y_BAR_PL4LL 25
# define Y_BAR_PL4LIC 26

# define Y_BAR_CD 4
# define Y_BAR_CDEL 6
# define Y_BAR_NL 8
# define Y_BAR_MCH 10
// # define
// # define
// # define

typedef	struct	s_curs
{
	int			pl_nb;
	int			bar_y_st;
	int 		key;
	int			pause;
}				t_curs;

void	ft_er_init(void);
void	ft_check_size_win(void);
void	colors(void);
void	make_border(t_curs *b);
void	make_bar(t_curs *b);
void	show_players(t_curs *b);
void	init_curs(t_curs **b);
void	exit_curse(t_curs *b);
int		curse(void);
#endif
