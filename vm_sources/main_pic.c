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
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

extern t_global	g_g;
extern t_curs	*g_b;

void	ft_er_init(void)
{
	ft_printf("ncurses problem with memory");
	system("kill $(pgrep afplay) > 1 > 2 > /dev/null");
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
	init_pair(1,  COLOR_GREEN,   COLOR_BLACK); // color first player
	init_pair(21, COLOR_BLACK, COLOR_GREEN); // swap color forst player
///////////////////////////////////////////////////////////////////////////
	init_pair(2,  COLOR_RED,     COLOR_BLACK); // color second player
	init_pair(22, COLOR_BLACK, COLOR_RED); // swap color second player
///////////////////////////////////////////////////////////////////////////
	init_pair(3,  COLOR_YELLOW,  COLOR_BLACK); // color third player
	init_pair(23, COLOR_BLACK, COLOR_YELLOW); // swap color third player
///////////////////////////////////////////////////////////////////////////
	init_pair(4,  COLOR_BLUE,    COLOR_BLACK); // color four player
	init_pair(24, COLOR_BLACK, COLOR_BLUE); // swap color four player
///////////////////////////////////////////////////////////////////////////
	init_pair(14, COLOR_CYAN, COLOR_BLACK); //color map
	init_pair(41, COLOR_BLACK, COLOR_CYAN); // swap map color
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
	init_pair(15, COLOR_WHITE, COLOR_BLACK); // white color for bar
	init_pair(17, COLOR_BLACK, COLOR_BLACK); // black color for space in map
	init_pair(18, COLOR_CYAN, COLOR_CYAN); // color border
}

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

void	show_players(void)
{
	if (g_b->pl_nb >= 1)
	{
		make_first_player();
		g_b->bar_y_st = Y_BAR_PL1;
	}
	if (g_b->pl_nb >= 2)
	{
		make_second_player();
		g_b->bar_y_st = Y_BAR_PL2;
	}
	if (g_b->pl_nb >= 3)
	{
		make_third_player();
		g_b->bar_y_st = Y_BAR_PL3;
	}
	if (g_b->pl_nb == 4)
	{
		make_fifth_player();
		g_b->bar_y_st = Y_BAR_PL4;
	}
	refresh();
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
	mvprintw(Y_BAR_PROC, X_BAR_SRT,"%s 0","Processes : ");
	show_players();
	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT,"%s","CYCLE_TO_DIE : 1536");
	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT,"%s","CYCLE_DELTA : 50");
	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT,"%s","NBR_LIVE : 21");
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT,"%s","MAX_CHECKS : 10");
}

void	print_color_p1(int *i)
{
	wattron(g_b->win, COLOR_PAIR(1));
	while (*i < g_g.players[0].startpos + g_g.players[0].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

void	print_color_p2(int *i)
{
	wattron(g_b->win, COLOR_PAIR(2));
	while (*i < g_g.players[1].startpos + g_g.players[1].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

void	print_color_p3(int *i)
{
	wattron(g_b->win, COLOR_PAIR(3));
	while (*i < g_g.players[2].startpos + g_g.players[2].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

void	print_color_p4(int *i)
{
	wattron(g_b->win, COLOR_PAIR(4));
	while (*i < g_g.players[3].startpos + g_g.players[3].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

void	print_map(void)
{
	wattron(g_b->win, COLOR_PAIR(14));
	refresh();
	int i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == g_g.players[0].startpos)
			print_color_p1(&i);
		else if (i == g_g.players[1].startpos)
			print_color_p2(&i);
		else if (i == g_g.players[2].startpos)
			print_color_p3(&i);
		else if (i == g_g.players[3].startpos)
			print_color_p4(&i);
		wprintw(g_b->win, " %02x", g_g.field[i]);
		if (i % 64 == 63)
			wprintw(g_b->win, "\n");
	}
	wrefresh(g_b->win);
}

/*
*** initil ncurse liblary
*/

void	print_cursor(void)
{
	refresh();
	int x;
	int y;

	if (g_b->pl_nb >= 1)
	{
		x = g_g.players[0].startpos % 64;
		y = g_g.players[0].startpos / 64;
		wmove(g_b->win, y, (x * 3));
		wattron(g_b->win, COLOR_PAIR(17));
		wprintw(g_b->win, " ");
		wattron(g_b->win, COLOR_PAIR(21));
		wprintw(g_b->win, "%02x", g_g.field[g_g.players[0].startpos]);
		wattron(g_b->win, COLOR_PAIR(14));
	}
	if (g_b->pl_nb >= 2)
	{
		x = g_g.players[1].startpos % 64;
		y = g_g.players[1].startpos / 64;
		wmove(g_b->win, y, (x * 3));
		wattron(g_b->win, COLOR_PAIR(17));
		wprintw(g_b->win, " ");
		wattron(g_b->win, COLOR_PAIR(22));
		wprintw(g_b->win, "%02x", g_g.field[g_g.players[1].startpos]);
		wattron(g_b->win, COLOR_PAIR(14));
	}
	if (g_b->pl_nb >= 3)
	{
		x = g_g.players[2].startpos % 64;
		y = g_g.players[2].startpos / 64;
		wmove(g_b->win, y, (x * 3));
		wattron(g_b->win, COLOR_PAIR(17));
		wprintw(g_b->win, " ");
		wattron(g_b->win, COLOR_PAIR(23));
		wprintw(g_b->win, "%02x", g_g.field[g_g.players[2].startpos]);
		wattron(g_b->win, COLOR_PAIR(14));
	}
	if (g_b->pl_nb == 4)
	{
		int x = g_g.players[3].startpos % 64;
		int y = g_g.players[3].startpos / 64;
		wmove(g_b->win, y, (x * 3));
		wattron(g_b->win, COLOR_PAIR(17));
		wprintw(g_b->win, " ");
		wattron(g_b->win, COLOR_PAIR(24));
		wprintw(g_b->win, "%02x", g_g.field[g_g.players[3].startpos]);
		wattron(g_b->win, COLOR_PAIR(14));
	}
	// refresh();
}

void	init_curs(void)
{
	g_b->pl_nb = g_g.num_of_players;
	if (!(initscr()))
		ft_er_init();
	ft_check_size_win();
//	system("afplay mp3/batle.mp3 &");
	curs_set(0);
	refresh();
	start_color();  // Инициализация цветов
	g_b->win = newwin(WIN_HEIGHT - 4, 194, 3, 3);
	colors();
	make_border();
	print_map();
	wattron(g_b->win, COLOR_PAIR(14));
	make_bar();
	print_cursor();
	refresh();
	wrefresh(g_b->win);
}

/*
*** free and exit ncurse liblary
*/

void	exit_curse(void)
{
	delwin(g_b->win);
	endwin();
//	system("kill $(pgrep afplay)");
//	system("kill $(pgrep afplay)");
	free(g_b);
	exit (0);
}

// void	erase_old(int index, t_curs *b)
// {
// 	int x;
// 	int y;
// //	int fd = open("1", O_RDWR);
// 	int res;

// 	x = (index % 64) * 3 + 1;
// 	y = index / 64;
// 	res = mvwinch(b->win, y, x);
// //	close(fd);
// }

void	draw_new(int index)
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

void	load_player(int index, int player)
{
	int x;
	int y;
	int i;

	i = -1;
	x = (index % 64) * 3;
	y = index / 64;
	wmove(g_b->win, y, x);
	wattron(g_b->win, COLOR_PAIR(2));
	while (++i < REG_SIZE)
	{
		wprintw(g_b->win, " %02x", g_g.field[index]);
		if (index % 64 == 63)
			wprintw(g_b->win, "\n");
		index++;
	}
	wrefresh(g_b->win);
}

/*
*** redraw bar every cycle to show change
*/

void	redraw_bar(void)
{
	refresh();
	attron(COLOR_PAIR(15) | A_BOLD);
//	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", "** PAUSED ** ");
	mvprintw(Y_BAR_SECL, X_BAR_SRT + 23,"%d ", g_b->sleep);
	mvprintw(Y_BAR_CYCL, X_BAR_SRT + 8,"%d", g_b->cycle);
//	mvprintw(Y_BAR_PROC, X_BAR_SRT,"%s 0","Processes : ");
//	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT,"%s","CYCLE_TO_DIE : 1536");
//	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT,"%s","CYCLE_DELTA : 50");
//	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT,"%s","NBR_LIVE : 21");
//	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT,"%s","MAX_CHECKS : 10");
}

/*
*** hotkay
*/

void		hotkey(void)
{
	if (g_b->key == 27)
		exit_curse();
 	if (g_b->key == 49 && g_b->sleep > 10000)
		g_b->sleep -= 10000;
	if (g_b->key == 50 && g_b->sleep < 600000)
		g_b->sleep += 10000;
	redraw_bar();
}

/*
*** pause
*/

void		pause_key(void)
{
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** STOPPED **");
	g_b->key = 0;
	while (g_b->key != 32)
	{
		g_b->key = getch();
		hotkey();
	}
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT,"%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** STOPPED **");
}

void	pashalka(void)
{
	int fd;
	int y = 0;
	int ret;
	char *line;
	
	fd = open("mp3/pas", O_RDONLY);
	wattron(g_b->win, COLOR_PAIR(2));
	while ((ret = get_next_line(fd, &line)))
	{
		mvwprintw(g_b->win, y, 0,"%s", line);
		free(line);
		y++;
	}
	close(fd);
	wrefresh(g_b->win);
	system("kill $(pgrep afplay)");
	system("afplay mp3/mario.mp3");
}

/*
*** Call from main
*/

void		readkey(void)
{
 	timeout(g_b->timeout);
	g_b->key = getch();
	hotkey();
 	if (g_b->key == 32)
		pause_key();
	usleep(g_b->sleep);
	g_b->key = 0;
}

/*
*** first draw map
*/

void		curse(void)
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
