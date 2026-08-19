/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   main.c                                            :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:10:02 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 11:15:28 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/coder.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int	init_coders(t_coder **coders, pthread_t **threads,
				t_dongle **dongles, t_ctx *ctx);

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_coder		*coders;
	t_dongle	*dongles;
	t_ctx		ctx;
	ssize_t		i;

	if (argc != 9 || get_args(argv, &ctx) || ctx.coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'\n");
		return (1);
	}
	threads = malloc(sizeof(pthread_t) * ctx.coders);
	coders = malloc(sizeof(t_coder) * ctx.coders);
	dongles = malloc(sizeof(t_dongle) * ctx.coders);
	if (!threads || !coders
		|| init_coders(&coders, &threads, &dongles, &ctx))
		return (2);
	i = -1;
	while (i++ < (ctx.coders - 1))
		if (pthread_join(threads[i], NULL))
			return (3);
	free(threads);
	free(coders);
	free(dongles); // TODO: destroy mutexes within dongles
	return (0);
}

static int	init_coders(t_coder **coders, pthread_t **threads,
		t_dongle **dongles, t_ctx *ctx)
{
	ssize_t		i;

	i = -1;
	while (i++ < (ctx->coders - 1))
	{
		pthread_mutex_init(&(*dongles + i)->mutex, NULL);
		(*dongles + i)->is_available = true;
	}
	i = -1;
	while (i++ < (ctx->coders - 1))
	{
		coders[0][i] = (t_coder){.id = i, .ctx = ctx,
			.dongles = {*dongles + i,
			*dongles + ((i + 1) % ctx->coders)}};
		if (pthread_create(*threads + i, NULL, &wait_for_dongle, *coders + i))
			return (1);
	}
	return (0);
}
