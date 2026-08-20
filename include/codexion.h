/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   codexion.h                                        :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/15 17:04:47 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/20 11:54:40 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coder.h"
# include <stdbool.h>

# define MAX_THREADS 512

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_params
{
	unsigned int	n_coders;
	unsigned int	burnout_time;
	unsigned int	compile_time;
	unsigned int	debug_time;
	unsigned int	refactor_time;
	unsigned int	max_compiles;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;
}	t_params;

typedef struct s_ctx
{
	t_params		*params;
	bool			process;

	t_dongle		*dongles;
	t_coder			*coders;
}	t_ctx;

int				init_coders(t_ctx *ctx);
int				init_dongles(t_ctx *ctx);
void			*action_process(void *c);
int				get_args(char **argv, t_params *params);
long long		get_elapsed_time(void);

#endif
