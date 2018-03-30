/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:50:58 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/27 17:51:00 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"
#include <stdio.h>

extern t_global	g_g;
extern t_curs	*g_b;

// void	swap_two_col(int pair, unsigned int index)
// {
// /*	if (g_g.field[index] == 1)
// 	{
// 		wattron(g_b->win, COLOR_PAIR(pair + 30) | A_BOLD);
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, COLOR_PAIR(pair + 30) | A_BOLD);
// 	}
// 	else*/
// //	{
// 		wattron(g_b->win, COLOR_PAIR(pair + 20));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, COLOR_PAIR(pair + 20));
// //	}
// //	wprintw(g_b->win, "%02x", g_g.field[index]);
// }

// void	swap_one_back(int pair, unsigned int index)
// {
// 	wattron(g_b->win, COLOR_PAIR(pair));
// 	wprintw(g_b->win, "%02x", g_g.field[index]);
// 	wattroff(g_b->win, COLOR_PAIR(pair));

// }

// void	swap_cursor(unsigned int index)
// {
// 	int	res;

// 	res = mvwinch(g_b->win, index / 64, ((index % 64) * 3) + 1) & A_COLOR;
// 	if (res == COLOR_PAIR(1))
// 		swap_two_col(1, index);
// 	else if (res == COLOR_PAIR(21)/* || (res == COLOR_PAIR(31))*/)
// 		swap_one_back(1, index);
// 	else if (res == COLOR_PAIR(2))
// 		swap_two_col(2, index);
// 	else if (res == COLOR_PAIR(22)/* | (res == COLOR_PAIR(32))*/)
// 		swap_one_back(2, index);
// 	else if (res == COLOR_PAIR(3))
// 		swap_two_col(3, index);
// 	else if (res == COLOR_PAIR(23)/* | (res == COLOR_PAIR(33))*/)
// 		swap_one_back(3, index);
// 	else if (res == COLOR_PAIR(4))
// 		swap_two_col(4, index);
// 	else if (res == COLOR_PAIR(24)/* | (res == COLOR_PAIR(34))*/)
// 		swap_one_back(4, index);
// 	else if (res == COLOR_PAIR(14))
// 		swap_one_back(41, index);
// 	else if (res == COLOR_PAIR(41))
// 		swap_one_back(14, index);
// 	wrefresh(g_b->win);
// }

// void	swap_cursor(int index)
// {
// 	int res;

// 	refresh();
// 	res = mvwinch(g_b->win, index / 64, (index % 64) * 3 + 1) & A_COLOR;

// 	if (res == COLOR_PAIR(1))
// //		swap_two_col(1, index);
// 	{
// 		if (g_g.field[index] == 1) 
// 			wattron(g_b->win, COLOR_PAIR(31) | A_BOLD);
// 		else			
// 			wattron(g_b->win, COLOR_PAIR(21));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, A_BOLD);
// 	}
// 	else if ((res == COLOR_PAIR(21)) || (res == COLOR_PAIR(31)))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(1));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(2))
// 	{
// 		if (g_g.field[index] == 1)
// 			wattron(g_b->win, COLOR_PAIR(32) | A_BOLD);
// 		else			
// 			wattron(g_b->win, COLOR_PAIR(22));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, A_BOLD);
// 	}
// 	else if ((res == COLOR_PAIR(22)) | (res == COLOR_PAIR(32)))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(2));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(3))
// 	{
// 		if (g_g.field[index] == 1)
// 			wattron(g_b->win, COLOR_PAIR(33) | A_BOLD);
// 		else
// 			wattron(g_b->win, COLOR_PAIR(23));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, A_BOLD);
// 	}
// 	else if ((res == COLOR_PAIR(23)) | (res == COLOR_PAIR(33)))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(3));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(4))
// 	{
// 		if (g_g.field[index] == 1)
// 			wattron(g_b->win, COLOR_PAIR(34) | A_BOLD);
// 		else
// 			wattron(g_b->win, COLOR_PAIR(24));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 		wattroff(g_b->win, A_BOLD);
// 	}
// 	else if ((res == COLOR_PAIR(24)) | (res == COLOR_PAIR(34)))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(4));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(14))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(41));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(41))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(14));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	wrefresh(g_b->win);
// }

// void	swap_cursor(int index)
// {
// 	int x;
// 	int y;
// 	unsigned int res;

// 	x = (index % 64) * 3 + 1;
// 	y = index / 64;
// 	refresh();
// 	res = mvwinch(g_b->win, y, x) & A_COLOR;
// 	if (res == COLOR_PAIR(1))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(21));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(21))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(1));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(2))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(22));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(22))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(2));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(3))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(23));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(23))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(3));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(4))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(24));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(24))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(4));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(14))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(41));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	else if (res == COLOR_PAIR(41))
// 	{
// 		wattron(g_b->win, COLOR_PAIR(14));
// 		wprintw(g_b->win, "%02x", g_g.field[index]);
// 	}
// 	wrefresh(g_b->win);
// }


void	draw_new(int index)
{
	// if (g_g.total_cycle >=0 && g_g.total_cycle <= 2)
	// 	dprintf(g_b->fd3, "new g_g.total_cycle = %d, index = %d map[index] = %d\n", g_g.total_cycle, index, g_b->map[index]);
	if (g_b->map[index] == 0)
	{
		int x;
		int y;
		unsigned int res;
		refresh();
		wrefresh(g_b->win);
			x = ((index % 64) * 3) + 1;
			y = index / 64;
		res = mvwinch(g_b->win, y, x) & A_COLOR;
		// if (res == COLOR_PAIR(1))
		// {
		// 	wattron(g_b->win, COLOR_PAIR(21));
		// 	wprintw(g_b->win, "%02x", g_g.field[index]);
		// }
		if (res == COLOR_PAIR(1))
	//		swap_two_col(1, index);
		{
		if (g_g.field[index] == 1) 
			wattron(g_b->win, COLOR_PAIR(31) | A_BOLD);
		else			
			wattron(g_b->win, COLOR_PAIR(21));
		wprintw(g_b->win, "%02x", g_g.field[index]);
		wattroff(g_b->win, A_BOLD);
		}
		if (res == COLOR_PAIR(14))
		{
			wattron(g_b->win, COLOR_PAIR(41));
			wprintw(g_b->win, "%02x", g_g.field[index]);
		}
	}
	g_b->map[index] += 1;
	refresh();
	wrefresh(g_b->win);
}

void	erace_old(int index)
{
	// if (g_g.total_cycle >=0 && g_g.total_cycle <= 2)
	// 	dprintf(g_b->fd4, "old g_g.total_cycle = %d, index = %d map[index] = %d\n", g_g.total_cycle, index, g_b->map[index]);
	if (g_b->map[index] == 1)
	{
		int x;
		int y;
		unsigned int res;
		refresh();
		x = (index % 64) * 3 + 1;
		y = index / 64;
		res = mvwinch(g_b->win, y, x) & A_COLOR;
		if ((res == COLOR_PAIR(21)) || (res == COLOR_PAIR(31)))
		{
			wattron(g_b->win, COLOR_PAIR(1));
			wprintw(g_b->win, "%02x", g_g.field[index]);
		}
		// if (res == COLOR_PAIR(21))
		// {
		// 	wattron(g_b->win, COLOR_PAIR(1));
		// 	wprintw(g_b->win, "%02x", g_g.field[index]);
		// }
		if (res == COLOR_PAIR(41))
		{
			wattron(g_b->win, COLOR_PAIR(14));
			wprintw(g_b->win, "%02x", g_g.field[index]);
		}
		wrefresh(g_b->win);
	}
	--(g_b->map[index]);
}

void	load_player(int index, int player)
{
	int x;
	int y;

	x = (index % 64) * 3;
	y = index / 64;
	wmove(g_b->win, y, x);
	wattron(g_b->win, COLOR_PAIR(player + 1));
	wprintw(g_b->win, " %02x", g_g.field[index]);
	wattroff(g_b->win, COLOR_PAIR(player + 1));
	wrefresh(g_b->win);
}
