/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:54:23 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 14:54:27 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** hotkay
*/

void	hotkey(void)
{
	if (g_b->key == 27)
		exit_curse();
 	if (g_b->key == 49 && g_b->sleep > 5000)
		g_b->sleep -= 5000;
	if (g_b->key == 50 && g_b->sleep < 200000)
		g_b->sleep += 10000;
	redraw_bar();
}

/*
*** pause
*/

void	pause_key(void)
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

/*
*** Call from main
*/

void	readkey(void)
{
 	timeout(g_b->timeout);
	g_b->key = getch();
	hotkey();
 	if (g_b->key == 32)
		pause_key();
	usleep(g_b->sleep);
	g_b->key = 0;
}
