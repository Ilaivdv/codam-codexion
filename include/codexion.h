/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   codexion.h                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/10 11:33:27 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/10 22:04:31 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

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
