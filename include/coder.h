/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coder.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/11 14:05:25 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/11 14:40:23 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <stdbool.h>

typedef struct s_dongle
{
	bool	is_available;
	// something for the cooldown here
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
	t_coder_states	state;
	t_dongle		*dongles;
	bool			burnout;
}	t_coder;

#endif
