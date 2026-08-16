/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   codexion.h                                        :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/15 17:04:47 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/15 17:04:48 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_THREADS 512

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_ctx
{
	unsigned int	coders;
	unsigned int	burnout_time;
	unsigned int	compile_time;
	unsigned int	debug_time;
	unsigned int	refactor_time;
	unsigned int	max_compiles;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;
}	t_ctx;

int	get_args(char **argv, t_ctx *ctx);

#endif
