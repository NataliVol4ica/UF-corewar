/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:18 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:18 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "op.h"

typedef struct	s_champ
{
	int		index;
	char	*filename;
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
	int		field[CHAMP_MAX_SIZE];
	int		field_size;
}				t_champ;

#endif
