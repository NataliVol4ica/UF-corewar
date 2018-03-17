/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 21:06:22 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/16 21:06:23 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_H
# define PROC_H

typedef struct		s_proc
{
	int				live; //0 || 1 live or dead
	int 			nb; //nb proc for a visual;
	int				id; // id process (for visualization)
	int				last_live;
	int				live_in_cp;
	unsigned char	reg[16]; //reg bufer
	int				carry; // flag carry for our process
	int				pc; // cursor place on map
	int				sleep; //nb of cycles (wait before make a command)
	char			hash; // command hash
	char			*name;//for debag;	
	struct s_proc   *next;
}					t_proc;

t_proc *lst_proc_new_start(t_champ cur, int index);
void	lst_proc_push_back(t_proc **alst, t_proc *new);
void	lst_del_dead_proc(t_proc **alst);

#endif
