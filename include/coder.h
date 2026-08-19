/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.h                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:25 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 22:35:24 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <stdbool.h>
# include <pthread.h>
# include <pthread.h>

# define UPDATE_TICKS 500

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	unsigned int	cooldown_time;
	bool			is_available;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				compiles;
	t_dongle		*dongles[2];
	unsigned int	action_elapsed_time;
}	t_coder;

#endif
