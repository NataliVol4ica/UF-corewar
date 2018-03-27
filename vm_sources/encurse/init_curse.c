/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_curse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:36:10 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 14:36:11 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** START_COLORS
*/

void	colors(void)
{
	init_color(COLOR_CYAN, 300, 300, 300);
	init_pair(1,  COLOR_GREEN,   COLOR_BLACK); // color first player
	init_pair(21, COLOR_BLACK, COLOR_GREEN); // swap color forst player
	init_pair(31, COLOR_WHITE, COLOR_GREEN); // swap color first player live
	init_pair(2,  COLOR_RED,     COLOR_BLACK); // color second player
	init_pair(22, COLOR_BLACK, COLOR_RED); // swap color second player
	init_pair(32, COLOR_WHITE, COLOR_RED); // swap color second player live
	init_pair(3,  COLOR_YELLOW,  COLOR_BLACK); // color third player
	init_pair(23, COLOR_BLACK, COLOR_YELLOW); // swap color third player
	init_pair(33, COLOR_WHITE, COLOR_YELLOW); // swap color third player live
	init_pair(4,  COLOR_BLUE,    COLOR_BLACK); // color four player
	init_pair(24, COLOR_BLACK, COLOR_BLUE); // swap color four player
	init_pair(34, COLOR_WHITE, COLOR_BLUE); // swap color four player live
	init_pair(14, COLOR_CYAN, COLOR_BLACK); //color map
	init_pair(41, COLOR_BLACK, COLOR_CYAN); // swap map color
	init_pair(15, COLOR_WHITE, COLOR_BLACK); // white color for bar
	init_pair(17, COLOR_BLACK, COLOR_BLACK); // black color for space in map
	init_pair(18, COLOR_CYAN, COLOR_CYAN); // color border
}

void	init_curs(void)
{
	g_b->pl_nb = g_g.num_of_players;
	if (!(initscr()))
		ft_er_init();
	ft_check_size_win();
//	system("afplay mp3/batle.mp3 &");
	refresh();
	start_color();  // Инициализация цветов
	g_b->win = newwin(WIN_HEIGHT - 4, 194, 3, 3);
	colors();
	curs_set(0);
	bkgd(COLOR_PAIR(17)); //background color
	wbkgd(g_b->win, COLOR_PAIR(17)); //background color
	make_border();
	print_map();
	wattron(g_b->win, COLOR_PAIR(14));
	make_bar();
	print_cursor();
 	refresh();
	wrefresh(g_b->win);
}

/*
*** first draw map
*/

void	curse(void)
{ 
	// kill -SIGSTP $(pgrep afplay)
	// kill -SIGSTOP $(pgrep afplay)
	init_curs();
	noecho();
	while (g_b->key != 32)
	{
		g_b->key = getch();
		hotkey();
	}
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** STOPPED **");
}
