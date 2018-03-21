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

# include "encurse.h"
# include <stdio.h>
# include "vm.h"

extern t_global	g_g;

void	ft_er_init(void)
{
	ft_printf("ncurses problem with memory");
	system("kill $(pgrep afplay)");
	exit(0);
}

/*
*** CHECK WINDOW SIZE!!!!!!!!!!!!!!
*/

void	ft_check_size_win(void)
{
	if (COLS < WIN_WIDTH)
	{
		endwin();
		ft_printf("%s\n", "Too small window width!!! Min width must be 260 COLUMS");
		exit(0);
	}
	if (LINES < WIN_HEIGHT)
	{
		endwin();
		ft_printf("%s\n", "Too small window height!!! Min height must be 70 LINES");
		exit(0);
	}
}

/*
*** START_COLORS
*/

void	colors(void)
{
	init_color(COLOR_CYAN, 300, 300, 300);
	init_pair(1,  COLOR_GREEN,   COLOR_BLACK);
	init_pair(2,  COLOR_RED,     COLOR_BLACK);
	init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
	init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
	init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
	init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
	init_pair(8,  COLOR_WHITE,   COLOR_RED);
	init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
	init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
	init_pair(11, COLOR_WHITE,   COLOR_BLUE);
	init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK,   COLOR_CYAN);
	init_pair(14, COLOR_CYAN, COLOR_CYAN);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(16, COLOR_CYAN, COLOR_BLACK);
	init_pair(13, COLOR_BLACK,   COLOR_CYAN);
	init_pair(14, COLOR_CYAN, COLOR_CYAN);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(16, COLOR_CYAN, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);

/*
***
*/
	init_pair(21, COLOR_CYAN, COLOR_GREEN);
	init_pair(22, COLOR_CYAN, COLOR_RED);
	init_pair(23, COLOR_CYAN, COLOR_YELLOW);
	init_pair(24, COLOR_CYAN, COLOR_BLUE);
}

/*
*** MAKE BORDERS
*/

void	make_border(t_curs *b)
{
	int y;
	int x;

	y = 0;
	x = 0;
	attron(COLOR_PAIR(14));
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
//	wrefresh(win);
}

/*
*** make players
*/

void	make_first_player(void)
{
	mvprintw(Y_BAR_PL1, X_BAR_SRT,"%s","Player -1 : ");
	attron(COLOR_PAIR(1));
	mvprintw(Y_BAR_PL1, X_BAR_SRT + 12,"%s", g_g.players[0].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL1LL, X_BAR_SCL,"%s 0","Last live : ");
	mvprintw(Y_BAR_PL1LIC, X_BAR_SCL,"%s 0","Lives in current period : ");
}

void	make_second_player(void)
{
	mvprintw(Y_BAR_PL2, X_BAR_SRT,"%s", "Player -2 : ");
	attron(COLOR_PAIR(2));
	mvprintw(Y_BAR_PL2, X_BAR_SRT + 12,"%s", g_g.players[1].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL2LL, X_BAR_SCL,"%s 0","Last live : ");
	mvprintw(Y_BAR_PL2LIC, X_BAR_SCL,"%s 0","Lives in current period : ");
}

void	make_third_player(void)
{
	mvprintw(Y_BAR_PL3, X_BAR_SRT,"%s","Player -3 : ");
	attron(COLOR_PAIR(3));
	mvprintw(Y_BAR_PL3, X_BAR_SRT + 12,"%s", g_g.players[2].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL3LL, X_BAR_SCL,"%s 0","Last live : ");
	mvprintw(Y_BAR_PL3LIC, X_BAR_SCL,"%s 0","Lives in current period : ");
}

void	make_fifth_player(void)
{
	mvprintw(Y_BAR_PL4, X_BAR_SRT,"%s","Player -4 : ");
	attron(COLOR_PAIR(4));
	mvprintw(Y_BAR_PL4, X_BAR_SRT + 12,"%s", g_g.players[3].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL4LL, X_BAR_SCL,"%s 0","Last live : ");
	mvprintw(Y_BAR_PL4LIC, X_BAR_SCL,"%s 0","Lives in current period : ");
}

void	show_players(t_curs *b)
{
	if (b->pl_nb >= 1)
	{
		make_first_player();
		b->bar_y_st = Y_BAR_PL1;
	}
	if (b->pl_nb >= 2)
	{
		make_second_player();
		b->bar_y_st = Y_BAR_PL2;
	}
	if (b->pl_nb >= 3)
	{
		make_third_player();
		b->bar_y_st = Y_BAR_PL3;
	}
	if (b->pl_nb == 4)
	{
		make_fifth_player();
		b->bar_y_st = Y_BAR_PL4;
	}
	refresh();
}

/*
*** make right side bar
*/

void	make_bar(t_curs *b)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", "** PAUSED ** ");
	mvprintw(Y_BAR_SECL, X_BAR_SRT,"%s 1000", "Cycles/second limit :");
	mvprintw(Y_BAR_CYCL, X_BAR_SRT,"%s 0","Cycle :");
	mvprintw(Y_BAR_PROC, X_BAR_SRT,"%s 0","Processes : ");
	show_players(b);
	mvprintw(b->bar_y_st + Y_BAR_CD, X_BAR_SRT,"%s","CYCLE_TO_DIE : 1536");
	mvprintw(b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT,"%s","CYCLE_DELTA : 50");
	mvprintw(b->bar_y_st + Y_BAR_NL, X_BAR_SRT,"%s","NBR_LIVE : 21");
	mvprintw(b->bar_y_st + Y_BAR_MCH, X_BAR_SRT,"%s","MAX_CHECKS : 10");
}

void	print_color_p1(int *i, t_curs *b)
{
	wattron(b->win, COLOR_PAIR(1));
	while (*i < g_g.players[0].startpos + g_g.players[0].field_size)
	{
		wprintw(b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(b->win, "\n");
		(*i)++;
	}
	wattron(b->win, COLOR_PAIR(16));
}

void	print_color_p2(int *i, t_curs *b)
{
	wattron(b->win, COLOR_PAIR(2));
	while (*i < g_g.players[1].startpos + g_g.players[1].field_size)
	{
		wprintw(b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(b->win, "\n");
		(*i)++;
	}
	wattron(b->win, COLOR_PAIR(16));
}

void	print_color_p3(int *i, t_curs *b)
{
	wattron(b->win, COLOR_PAIR(3));
	while (*i < g_g.players[2].startpos + g_g.players[2].field_size)
	{
		wprintw(b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(b->win, "\n");
		(*i)++;
	}
	wattron(b->win, COLOR_PAIR(16));
}

void	print_color_p4(int *i, t_curs *b)
{
	wattron(b->win, COLOR_PAIR(4));
	while (*i < g_g.players[3].startpos + g_g.players[3].field_size)
	{
		wprintw(b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(b->win, "\n");
		(*i)++;
	}
	wattron(b->win, COLOR_PAIR(16));
}

void	print_map(t_curs *b)
{
	wattron(b->win, COLOR_PAIR(16));
	refresh();
	int i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == g_g.players[0].startpos)
			print_color_p1(&i, b);
		else if (i == g_g.players[1].startpos)
			print_color_p2(&i, b);
		else if (i == g_g.players[2].startpos)
			print_color_p3(&i, b);
		else if (i == g_g.players[3].startpos)
			print_color_p4(&i, b);
		wprintw(b->win, " %02x", g_g.field[i]);
		if (i % 64 == 63)
			wprintw(b->win, "\n");
	}
	wrefresh(b->win);
}

/*
*** initil ncurse liblary
*/

void	print_cursor(t_curs *b)
{
	refresh();
	int x;
	int y;
	if (b->pl_nb >= 1)
	{
		x = g_g.players[0].startpos % 64;
		y = g_g.players[0].startpos / 64;
		wmove(b->win, y, (x * 3));
		wattron(b->win, COLOR_PAIR(17));
		wprintw(b->win, " ");
		wattron(b->win, COLOR_PAIR(21));
		wprintw(b->win, "%02x", g_g.field[g_g.players[0].startpos]);
		wattron(b->win, COLOR_PAIR(16));
	}
	if (b->pl_nb >= 2)
	{
		x = g_g.players[1].startpos % 64;
		y = g_g.players[1].startpos / 64;
		wmove(b->win, y, (x * 3));
		wattron(b->win, COLOR_PAIR(17));
		wprintw(b->win, " ");
		wattron(b->win, COLOR_PAIR(22));
		wprintw(b->win, "%02x", g_g.field[g_g.players[1].startpos]);
		wattron(b->win, COLOR_PAIR(16));
	}
	if (b->pl_nb >= 3)
	{
		x = g_g.players[2].startpos % 64;
		y = g_g.players[2].startpos / 64;
		wmove(b->win, y, (x * 3));
		wattron(b->win, COLOR_PAIR(17));
		wprintw(b->win, " ");
		wattron(b->win, COLOR_PAIR(23));
		wprintw(b->win, "%02x", g_g.field[g_g.players[2].startpos]);
		wattron(b->win, COLOR_PAIR(16));
	}
	if (b->pl_nb == 4)
	{
		int x = g_g.players[3].startpos % 64;
		int y = g_g.players[3].startpos / 64;
		wmove(b->win, y, (x * 3));
		wattron(b->win, COLOR_PAIR(17));
		wprintw(b->win, " ");
		wattron(b->win, COLOR_PAIR(24));
		wprintw(b->win, "%02x", g_g.field[g_g.players[3].startpos]);
		wattron(b->win, COLOR_PAIR(16));
	}
	// refresh();
}

void	init_curs(t_curs **b)
{
	*b = ft_memalloc(sizeof(t_curs));
	(*b)->pl_nb = g_g.num_of_players;
	if (!(initscr()))
		ft_er_init();
	ft_check_size_win();
	system("afplay mp3/batle.mp3 &");
	curs_set(0);
	refresh();
	start_color();  // Инициализация цветов
	(*b)->win = newwin(WIN_HEIGHT - 4, 194, 3, 3);
	colors();
	make_border(*b);
	print_map(*b);
	wattron((*b)->win, COLOR_PAIR(14));
	make_bar(*b);
	print_cursor(*b);
	refresh();
	wrefresh((*b)->win);
}

/*
*** free and exit ncurse liblary
*/

void	exit_curse(t_curs *b)
{
	delwin(b->win);
	endwin();
	system("kill $(pgrep afplay)");
	free(b);
	exit (0);
}

int		curse(void)
{
	t_curs	*b;
//	int fd = open("1", O_RDWR);
	// kill -SIGSTP $(pgrep afplay)
	// kill -SIGSTOP $(pgrep afplay)
	init_curs(&b);
	noecho();
//	refresh();
	while (b->key != 27)
	{
		b->key = getch();
// //		if (b->key == 27)
// //		{
// //			close(fd);
// 			exit_curse(b);
// 		}
		if (b->key == 32)
		{
			b->pause = (b->pause == 0 ? 1 : 0);
			mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", b->pause == 0 ? "** PAUSED ** " : "** STOPPED **");
		}
		// if (b->key == 49)
		// 	system("kill -SIGSTOP $(pgrep afplay) > /dev/null");
		// if (b->key == 50)
		// 	system("kill -SIGSTP $(pgrep afplay) > /dev/null");
//		dprintf(fd, "key %d", b->key);
	}
//	close(fd);
	exit_curse(b);
	return (0);
}