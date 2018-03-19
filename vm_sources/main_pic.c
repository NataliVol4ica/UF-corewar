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

//# include "encurse.h"
# include <stdio.h>
//# include <ncurses.h>
//# include <curses.h>
# include "vm.h"

extern WINDOW *win;

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
	init_pair(1,  COLOR_RED,     COLOR_RED);
	init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
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
	wattron(win, COLOR_PAIR(14));
	while (y < WIN_HEIGHT - 1)
	{
		mvwaddch(win, y, 0, '@');
		mvwaddch(win, y, 195, '@');
		mvwaddch(win, y, 258, '@');
		y++;
	}
	while (x < WIN_WIDTH - 1)
	{
		mvwaddch(win, 0, x, '@');
		mvwaddch(win, WIN_HEIGHT - 1, x, '@');
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
	mvprintw(Y_BAR_PL1LL, X_BAR_SCL,"%s","Last live : ");
	mvprintw(Y_BAR_PL1LIC, X_BAR_SCL,"%s","Lives in current period : ");
}

void	make_second_player(void)
{
	mvprintw(Y_BAR_PL2, X_BAR_SRT,"%s","Player -2 : ");
	mvprintw(Y_BAR_PL2LL, X_BAR_SCL,"%s","Last live : ");
	mvprintw(Y_BAR_PL2LIC, X_BAR_SCL,"%s","Lives in current period : ");
}

void	make_third_player(void)
{
	mvprintw(Y_BAR_PL3, X_BAR_SRT,"%s","Player -3 : ");
	mvprintw(Y_BAR_PL3LL, X_BAR_SCL,"%s","Last live : ");
	mvprintw(Y_BAR_PL3LIC, X_BAR_SCL,"%s","Lives in current period : ");
}

void	make_fifth_player(void)
{
	mvprintw(Y_BAR_PL4, X_BAR_SRT,"%s","Player -4 : ");
	mvprintw(Y_BAR_PL4LL, X_BAR_SCL,"%s","Last live : ");
	mvprintw(Y_BAR_PL4LIC, X_BAR_SCL,"%s","Lives in current period : ");
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
}

/*
*** make right side bar
*/

void	make_bar(t_curs *b)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", "** PAUSED ** ");
	mvprintw(Y_BAR_SECL, X_BAR_SRT,"%s", "Cycles/second limit :");
	mvprintw(Y_BAR_CYCL, X_BAR_SRT,"%s","Cycle :");
	mvprintw(Y_BAR_PROC, X_BAR_SRT,"%s","Processes : ");
	show_players(b);
	mvprintw(b->bar_y_st + Y_BAR_CD, X_BAR_SRT,"%s","CYCLE_TO_DIE : ");
	mvprintw(b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT,"%s","CYCLE_DELTA : ");
	mvprintw(b->bar_y_st + Y_BAR_NL, X_BAR_SRT,"%s","NBR_LIVE : ");
	mvprintw(b->bar_y_st + Y_BAR_MCH, X_BAR_SRT,"%s","MAX_CHECKS : ");
}

/*
*** initil ncurse liblary
*/

void	init_curs(t_curs **b)
{
	*b = ft_memalloc(sizeof(t_curs));
	(*b)->pl_nb = 4;

	if (!(initscr()))
		ft_er_init();
	ft_check_size_win();
//	system("afplay batle.mp3 &");
	curs_set(0);
	win = newwin(WIN_HEIGHT, WIN_WIDTH, 0, 0);
	refresh();
	start_color();  // Инициализация цветов
	colors();
	make_border(*b);
	wattron(win, COLOR_PAIR(14));
	make_bar(*b);
	wrefresh(win);
}

/*
*** free and exit ncurse liblary
*/

void	exit_curse(t_curs *b)
{
	delwin(win);
	endwin();
//	system("kill $(pgrep afplay)");
	free(b);pwd
	exit (0);
}

// void	print_map(t_curs *b)
// {

// }

int		curse(void)
{
	t_curs	*b;
//	int fd = open("1", O_RDWR);
	// kill -SIGSTP $(pgrep afplay)
	// kill -SIGSTOP $(pgrep afplay)
	init_curs(&b);
	noecho();
//	print_map(b);
	while (1)
	{
		b->key = getch();
		if (b->key == 27)
		{
//			close(fd);
			exit_curse(b);
		}
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