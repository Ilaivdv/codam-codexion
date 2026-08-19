/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   codexion.h                                        :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/15 17:04:47 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 22:24:27 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coder.h"
# include <stdbool.h>
# include <sys/time.h>

# define MAX_THREADS 512

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_ctx
{
	unsigned int	n_coders;
	unsigned int	burnout_time;
	unsigned int	compile_time;
	unsigned int	debug_time;
	unsigned int	refactor_time;
	unsigned int	max_compiles;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;
}	t_ctx;

typedef struct s_monitor
{
	t_ctx			*ctx;
	bool			process;

	t_dongle		*dongles;
	t_coder			*coders;
}	t_monitor;

int				init_coders(t_monitor *mntr);
void			*wait_for_dongle(void *p);
int				get_args(char **argv, t_ctx *ctx);
unsigned int	get_elapsed_time(t_ctx *ctx);

#endif
