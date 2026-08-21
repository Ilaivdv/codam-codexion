/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   utils.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:27:50 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/21 14:44:43 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int	get_args(char **argv, t_params *ctx)
{
	*ctx = (t_params){.n_coders = atoi(argv[1]),
		.burnout_time = atoi(argv[2]) * 1000,
		.compile_time = atoi(argv[3]) * 1000,
		.debug_time = atoi(argv[4]) * 1000,
		.refactor_time = atoi(argv[5]) * 1000,
		.max_compiles = atoi(argv[6]),
		.dongle_cooldown = atoi(argv[7]) * 1000};
	if (!strcmp(argv[8], "fifo"))
		ctx->scheduler = FIFO;
	else if (!strcmp(argv[8], "edf"))
		ctx->scheduler = EDF;
	else
		return (1);
	while (argv++ && *(argv + 1) != NULL)
		if (atoi(*argv) <= 0)
			return (1);
	return (0);
}

// returns time elapsed (in us), since the start of the program
int64_t	get_elapsed_time(void)
{
	static int64_t	epoch = -1;
	struct timeval	tv;
	int64_t			current_time;

	gettimeofday(&tv, NULL);
	if (epoch == -1)
		epoch = tv.tv_usec;
	current_time = tv.tv_usec;
	return (current_time - epoch);
}

// gets queue cmp value based on scheduler
int64_t	get_cmp(t_coder *coder)
{
	if (coder->ctx->params->scheduler == FIFO)
		return (get_elapsed_time());
	else
		return (coder->deadline - get_elapsed_time());
}
