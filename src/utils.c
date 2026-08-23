/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   utils.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:27:50 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 16:54:59 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int	get_args(int argc, char **argv, t_params *ctx)
{
	if (argc != 9)
		return (1);
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

int64_t	get_elapsed_time(bool in_ms)
{
	static int64_t	epoch = -1;
	struct timeval	tv;
	int64_t			current_time;

	gettimeofday(&tv, NULL);
	if (epoch == -1)
		epoch = tv.tv_usec;
	current_time = tv.tv_usec;
	if (in_ms)
		return ((current_time - epoch) / 1000);
	return (current_time - epoch);
}

int64_t	get_cmp(t_coder *coder)
{
	if (coder->ctx->params->scheduler == FIFO)
		return (get_elapsed_time(false));
	else
		return (coder->deadline - get_elapsed_time(false));
}

void	cleanup(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
		pthread_mutex_destroy(&ctx->dongles[i].mutex);
	pthread_mutex_destroy(&ctx->coder_action_mutex);
	free(ctx->coders);
	free(ctx->dongles);
}
