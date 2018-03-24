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

# include <stdio.h>
# include <stdlib.h>
# include <ncurses.h>

# define WIN_WIDTH 260
# define WIN_HEIGHT 70

# define X_MATR_SRT 4
# define Y_MATR_SRT 3
# define X_MATR_END 196
# define Y_MATR_END 68

# define X_BAR_SRT 206
# define Y_BAR_SRT 3
# define Y_BAR_SECL 5
# define Y_BAR_CYCL 9
# define Y_BAR_PROC 11

# define Y_BAR_PL1 13
# define Y_BAR_PL1LL 14
# define Y_BAR_PL1LIC 15
# define X_BAR_SCL 206

# define Y_BAR_PL2 17
# define Y_BAR_PL2LL 18
# define Y_BAR_PL2LIC 19

# define Y_BAR_PL3 21
# define Y_BAR_PL3LL 22
# define Y_BAR_PL3LIC 23

# define Y_BAR_PL4 25
# define Y_BAR_PL4LL 26
# define Y_BAR_PL4LIC 27

# define Y_BAR_CD 4
# define Y_BAR_CDEL 6
# define Y_BAR_NL 8
# define Y_BAR_MCH 10

typedef	struct	s_curs
{
	WINDOW		*win;
	int			pl_nb;
	int			bar_y_st;
	int 		key;
	int			pause;
	int 		cycle;
	uint32_t	sleep;
	uint8_t		timeout;
}				t_curs;

void			ft_er_init(void);
void			ft_check_size_win(void);
void			colors(void);
void			make_border(void);
void			make_bar(void);
void			show_players(void);
void			init_curs(void);
void			exit_curse(void);
void			curse(void);
void			draw_new(int index);
void			readkey(void);
void			redraw_bar(void);
void			hooks(void);
void			load_player(int index, int player);
void			pashalka(void);

#endif
