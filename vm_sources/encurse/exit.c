/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:43:01 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 13:43:07 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_curs	*g_b;

void		ft_er_init(void)
{
	ft_printf("ncurses problem with memory");
//	system("kill $(pgrep afplay) > 1 > 2 > /dev/null");
	exit(0);
}

/*
*** CHECK WINDOW SIZE!!!!!!!!!!!!!!
*/

void		ft_check_size_win(void)
{
	if (COLS < WIN_WIDTH)
	{
		endwin();
		ft_printf("%s\n", "Too small window width!!! Min width must"
			" be 260 COLUMS");
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
*** free and exit ncurse liblary
*/

void		exit_curse(void)
{
	delwin(g_b->win);
	endwin();
	// system("kill $(pgrep afplay)");
	// system("kill $(pgrep afplay)");
	free(g_b);
	exit(0);
}

void		exit_curse_main(void)
{
	delwin(g_b->win);
	endwin();
//	system("kill $(pgrep afplay)");
//	system("kill $(pgrep afplay)");
	free(g_b);
}

void		pashalka(void)
{
	int		fd;
	int		y;
	int		ret;
	char	*line;
	
	y = 0;
	fd = open("mp3/pas", O_RDONLY);
	wattron(g_b->win, COLOR_PAIR(2));
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == 0)
			exit(0);
		mvwprintw(g_b->win, y, 0,"%s", line);
		free(line);
		y++;
	}
	close(fd);
	wrefresh(g_b->win);
	// system("kill $(pgrep afplay)");
	// system("afplay mp3/mario.mp3");
}
