/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coder.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/11 14:05:25 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/12 14:43:27 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <stdbool.h>

typedef struct s_dongle
{
	unsigned int	cooldown_time;
	bool			is_available;
}	t_dongle;

typedef enum s_coder_states
{
	WAITING,
	COMPILING,
	DEBUGGING,
	REFACTORING,
}	t_coder_states;

typedef struct s_coder
{
	int				coder_id;
	t_coder_states	state;
	t_dongle		dongles[2];
	bool			burnout;
}	t_coder;

void	*coder_get_dongle(void *c);

#endif
