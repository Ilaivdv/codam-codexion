/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.h                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:25 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/18 20:19:29 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "codexion.h"
# include <stdbool.h>
# include <pthread.h>

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	unsigned int	cooldown_time;
	bool			is_available;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	t_ctx			*ctx;
	t_dongle		*dongles[2];
	bool			burnout;
	int				compiles;
}	t_coder;

void	*wait_for_dongle(void *p);

#endif
