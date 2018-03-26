/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   main_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 13:39:49 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/18 13:39:50 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** MAKE BORDERS
*/

void	make_border(void)
{
	int y;
	int x;

	y = 0;
	x = 0;
	refresh();
	attron(COLOR_PAIR(18));
	while (y < WIN_HEIGHT - 1)
	{
		mvaddch(y, 0, '@');
		mvaddch(y, 198, '@');
		mvaddch(y, 258, '@');
		y++;
	}
	while (x < WIN_WIDTH - 1)
	{
		mvaddch(0, x, '@');
		mvaddch(WIN_HEIGHT - 1, x, '@');
		x++;
	}
	wrefresh(g_b->win);
}

/*
*** make right side bar
*/

void	make_bar(void)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", "** PAUSED ** ");
	mvprintw(Y_BAR_SECL, X_BAR_SRT,"%s %d", "Cycles/second limit : ", g_b->sleep);
	mvprintw(Y_BAR_CYCL, X_BAR_SRT,"%s %d","Cycle :", g_b->cycle);
	mvprintw(Y_BAR_PROC, X_BAR_SRT,"%s","Processes : ");
	show_players();
	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT,"%s%d ","CYCLE_TO_DIE : ", CYCLE_TO_DIE);
	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT,"%s %d","CYCLE_DELTA : ", CYCLE_DELTA);
	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT,"%s %d   ","NBR_LIVE :    ", NBR_LIVE);
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT,"%s  %d","MAX_CHECKS : ", MAX_CHECKS);
}


/*
*** initil ncurse liblary
*/

void	print_cursor(void)
{
//	refresh();
	int x;
	int y;

	if (g_b->pl_nb >= 1)
	{
		g_b->map[g_g.players[0].startpos] = 1;
		swap_cursor(g_g.players[0].startpos);
	}
	if (g_b->pl_nb >= 2)
	{
		g_b->map[g_g.players[1].startpos] = 1;
		swap_cursor(g_g.players[1].startpos);
	}
	if (g_b->pl_nb >= 3)
	{
		g_b->map[g_g.players[2].startpos] = 1;
		swap_cursor(g_g.players[2].startpos);
	}
	if (g_b->pl_nb == 4)
	{
		g_b->map[g_g.players[3].startpos] = 1;
		swap_cursor(g_g.players[3].startpos);
	}
	refresh();
}

void	swap_cursor(int index)
{
	int x;
	int y;
	int res;

	x = (index % 64) * 3 + 1;
	y = index / 64;
	refresh();
	res = mvwinch(g_b->win, y, x) & A_COLOR;
	if (res == COLOR_PAIR(1))
	{
		wattron(g_b->win, COLOR_PAIR(21));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(21))
	{
		wattron(g_b->win, COLOR_PAIR(1));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(2))
	{
		wattron(g_b->win, COLOR_PAIR(22));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(22))
	{
		wattron(g_b->win, COLOR_PAIR(2));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(3))
	{
		wattron(g_b->win, COLOR_PAIR(23));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(23))
	{
		wattron(g_b->win, COLOR_PAIR(3));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(4))
	{
		wattron(g_b->win, COLOR_PAIR(24));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(24))
	{
		wattron(g_b->win, COLOR_PAIR(4));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(14))
	{
		wattron(g_b->win, COLOR_PAIR(41));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	else if (res == COLOR_PAIR(41))
	{
		wattron(g_b->win, COLOR_PAIR(14));
		wprintw(g_b->win, "%02x", g_g.field[index]);
	}
	wrefresh(g_b->win);
}

void	draw_new(int index)
{
	g_b->map[index] += 1;
	if (g_b->map[index] == 1)
		swap_cursor(index);
}

void	erace_old(int index)
{
	g_b->map[index] -= 1;
	if (g_b->map[index] == 0)
		swap_cursor(index);
}

void	load_player(int index, int player)
{
	int x;
	int y;
	// int i;

	// i = -1;
	x = (index % 64) * 3;
	y = index / 64;
	wmove(g_b->win, y, x);
	wattron(g_b->win, COLOR_PAIR(player + 1));
	// while (++i < REG_SIZE)
	// {
	wprintw(g_b->win, " %02x", g_g.field[index]);
	// 	if (index % 64 == 63)
	// 		wprintw(g_b->win, "\n");
	// 	index++;
	// }
	wrefresh(g_b->win);
}

/*
*** redraw bar every cycle to show change
*/

void	redraw_bar(void)
{
	refresh();
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SECL, X_BAR_SRT + 23,"%d ", g_b->sleep);
	mvprintw(Y_BAR_CYCL, X_BAR_SRT + 8,"%d", g_b->cycle);
	if (g_b->pl_nb >= 1)
	{
//		mvprintw(Y_BAR_PL1LL, X_BAR_SCL + 26,"%d", g_g.live[0]);
		mvprintw(Y_BAR_PL1LIC, X_BAR_SCL + 26,"%d",g_g.live[0]);
	}
	if (g_b->pl_nb >= 2)
	{
//		mvprintw(Y_BAR_PL2LL, X_BAR_SCL + 26,"%d", g_g.live[1]);
		mvprintw(Y_BAR_PL2LIC, X_BAR_SCL + 26,"%d", g_g.live[1]);
	}
	if (g_b->pl_nb >= 3)
	{
		mvprintw(Y_BAR_PL3LL, X_BAR_SCL + 26,"%d", g_g.live[2]);
//		mvprintw(Y_BAR_PL3LIC, X_BAR_SCL + 26,"%d",);
	}
	if (g_b->pl_nb == 4)
	{
		mvprintw(Y_BAR_PL4LL, X_BAR_SCL + 26,"%d", g_g.live[3]);
//		mvprintw(Y_BAR_PL4LIC, X_BAR_SCL + 26,"%d",);
	}
	mvprintw(Y_BAR_PROC, X_BAR_SRT + 15,"%d", g_g.num_of_processes);
	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT + 15,"%d ", g_g.cycle_to_die);
	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT + 15, "%d " ,CYCLE_DELTA);
	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT + 15, "%d ", NBR_LIVE);
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT + 14, " %d  ", MAX_CHECKS - g_g.checks);
	wrefresh(g_b->win);
}
